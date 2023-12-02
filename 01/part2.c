#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool {
    false = 0,
    true
}
bool;

/* A slightly better str. For static allocations */
struct String {
    const char *s;
    uint32_t  len;
};
typedef struct String
String;

/* For dynamic allocations */
struct DynamicString {
    int32_t  len;
    int32_t size;
    char s[];
};
typedef struct DynamicString
DynString;

/* A somewhat reasonable grow size */
#define GROW 64

/* useful string macros */
#define     lengthof(str) (str.len)
#define get_lengthof(str) (str->len)
#define      str_arr(str) (str.s)
#define  get_str_arr(str) (str->s)

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

/* DynString "methods" */
DynString *dyn_string_birth(void);
void dyn_string_append(DynString **, char c);
void dyn_string_kill(DynString *);
bool dyn_string_get_file_line(DynString **dstr, FILE *file);
void dyn_string_print(DynString *str);
void dyn_string_part_print(DynString *str, int idx);

int main(int argc, const char *argv[]){
    if (argc != 2){
        printf("Usage: %s INPUT.txt\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file){
        printf("Error: Could not find %s\n", argv[1]);
        return 2;
    }
    
    /** Here we parse the input, interpret words on the fly
     ** and continue the operation in the same way as part 1
     ** just with a few extra cases.
     **/
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
    }

    printf("sum of calibration values: %d\n", sum);

    fclose(file);
    dyn_string_kill(str);
    return 0;
}

/* a "perfect" translation hash */
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

/* return the dictionary translation of the word */
uint32_t translate(String * restrict str){
    const char *s = get_str_arr(str);
    if (strncmp(s, str_arr(mini_dictionary[hash(s)].key), get_lengthof(str)) != 0)
        return MISSING;
    return mini_dictionary[hash(s)].value;
}

DynString *dyn_string_birth(void){
    DynString *new = malloc(sizeof(*new) + GROW * sizeof(*(new->s)));
    new->len = 0;
    new->size = GROW;
    return new;
}

void dyn_string_append(DynString **dstr, char c){
    if ((*dstr)->len == (*dstr)->size){
    /** yes i know this is bad practice, but it's a light problem, not an API */
       *dstr = realloc(*dstr, sizeof(**dstr) + (GROW + (*dstr)->size) * sizeof(*((*dstr)->s)));
        (*dstr)->size += GROW;
    }

    (*dstr)->s[(*dstr)->len] = c;
    ++(*dstr)->len;
}

void dyn_string_kill(DynString *dstr){
    free(dstr);
}

bool dyn_string_get_file_line(DynString **dstr, FILE *file){
    if (*dstr){
        dyn_string_kill(*dstr);
        *dstr = dyn_string_birth();
    }
    else
        *dstr = dyn_string_birth();

    char c;
    bool break_loop = false;
    while (fread(&c, sizeof(c), 1, file)){
        if (c == '\n'){
            break_loop = true;
            break;
        }
        dyn_string_append(dstr, c);
    }
    return break_loop;
}

void dyn_string_print(DynString *str){
    printf("str: ");
    for (int i = 0; i < get_lengthof(str); ++i)
        putchar(get_str_arr(str)[i]);
    puts("");
}

void dyn_string_part_print(DynString *str, int idx){
    printf("str[%d:]: ", idx);
    for (int i = idx; i < get_lengthof(str); ++i)
        putchar(get_str_arr(str)[i]);
    puts("");
}
