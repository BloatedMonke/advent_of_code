#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "dyn_string.h"

/* A slightly better str. For static allocations */
struct String {
    const char *s;
    uint32_t  len;
};
typedef struct String
String;

struct KeyValuePair {
    String     key;
    uint32_t value;
};
typedef struct KeyValuePair
KeyValuePair;

#define WORD_COUNT 9
/* Forcing a "perfect" hashtable as problem size is small.
 * Don't overengineer the solution ;) */
KeyValuePair mini_dictionary[WORD_COUNT] = 
{
    {.key = {.s =   "one", .len = 3}, .value =  1},
    {.key = {.s =   "two", .len = 3}, .value =  2},
    {.key = {.s = "three", .len = 5}, .value =  3},
    {.key = {.s =  "four", .len = 4}, .value =  4},
    {.key = {.s =  "five", .len = 4}, .value =  5},
    {.key = {.s =   "six", .len = 3}, .value =  6},
    {.key = {.s = "seven", .len = 5}, .value =  7},
    {.key = {.s = "eight", .len = 5}, .value =  8},
    {.key = {.s =  "nine", .len = 4}, .value =  9}
};
/* Arbitrary choice > 8 that should hopefully yield a
 * seg fault if mistakenly read from */
#define OUT_OF_BOUNDS 0xff
#define MISSING OUT_OF_BOUNDS

/* Nice for natural reading */
#define IS_NOT !=

/* Ensure we don't read past the bounds of the string */
#define MIN_WIDTH 3

/* Prototypes */
uint32_t hash(const char *);
uint32_t translate(String * restrict str);

uint32_t part_1(FILE *);
uint32_t part_2(FILE *);

int main(int argc, const char *argv[])
{
    if (argc != 2){
        printf("Usage: %s INPUT_FILE.txt\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file){
        printf("Error: Could not find %s\n", argv[1]);
        return 2;
    }

    uint32_t sum1 = part_1(file);
    rewind(file);
    uint32_t sum2 = part_2(file);
    fclose(file);

    printf("sum of calibration values::\n");
    printf("Part 1: %d\n", sum1);
    printf("Part 2: %d\n", sum2);

    return 0;
}

uint32_t part_1(FILE *file){
    char c;
    int sum = 0;
    bool you_are_the_first = true;
    while (fread(&c, sizeof(c), 1, file)){
        int first_num, last_num, num;
        
        if (isdigit(c))
            num = c - '0';
        if (isdigit(c) && you_are_the_first){
            first_num = c - '0';
            you_are_the_first = false;
        }
        /* assumes last line also has a newline */
        if (c == '\n'){
            last_num = num;
            sum += first_num * 10 + last_num;
            you_are_the_first = true;
            first_num = last_num = num = 0;
        }
    }
    return sum;
}

/* Here we parse the input, interpret words on the fly
 * and continue the operation in the same way as part 1
 * just with a few extra cases.
 */
uint32_t part_2(FILE *file){
    int sum = 0;
    bool you_are_the_first = true;
    DynString *str = NULL;
    while (dyn_string_get_file_line(&str, file)){
        const char * const s = get_str_arr(str);
        int first_num, last_num, num;
        int test_num = MISSING;
        String lex;
        for (int i = 0; i < get_lengthof(str); ++i){
            if (isdigit(s[i]))
                num = s[i] - '0';
            if (isdigit(s[i]) && you_are_the_first){
                first_num = s[i] - '0';
                you_are_the_first = false;
            }
            if (hash(s + i) IS_NOT OUT_OF_BOUNDS)
            if ((get_lengthof(str) - i) >= MIN_WIDTH){
                lex.s = (s+i);
                lex.len = mini_dictionary[hash(s + i)].key.len;
                test_num = translate(&lex);
              }
            
            if (test_num IS_NOT MISSING){
                num = test_num;
            
            /** push forward so it doesn't waste time
             ** on the same word */
                i += mini_dictionary[hash(s + i)].key.len - 1;
            
            /** for cases like eightwo:: 82 */
                i -= i > 0 ? 1: 0;
            }
            if (test_num IS_NOT MISSING && you_are_the_first){
                first_num = test_num;
                you_are_the_first = false;
            }
            if (i == get_lengthof(str) - 1){
                last_num = num;
                sum += first_num * 10 + last_num;
                you_are_the_first = true;
            }
            test_num = MISSING;
        }
        first_num = last_num = num = 0;
        dyn_string_kill(str);
    }
    dyn_string_kill(str);
    return sum;
}

/* A "perfect" translation hash */
uint32_t hash(const char *s){
    switch (s[0]){
    case 'o':
        return 0;
    case 't':
        if (s[1] == 'w') return 1;
        else return 2;
    case 'f':
        if (s[1] == 'o') return 3;
        else return 4;
    case 's':
        if (s[1] == 'i') return 5;
        else return 6;
    case 'e':
        return 7;
    case 'n':
        return 8;
    default:
        return OUT_OF_BOUNDS;
    }
}

/* Return the dictionary translation of the word */
uint32_t translate(String * restrict str){
    const char *s = get_str_arr(str);
    if (strncmp(s, str_arr(mini_dictionary[hash(s)].key), get_lengthof(str)) != 0)
        return MISSING;
    return mini_dictionary[hash(s)].value;
}
