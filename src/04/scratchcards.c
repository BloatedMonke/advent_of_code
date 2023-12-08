#include <ctype.h>
#include <stdio.h>
#include "dyn_string.h"
#include "utility.h"

#ifndef FILE_LENGTH
#define FILE_LENGTH 198
#endif

uint32_t solve(FILE *file, int my_len);
uint32_t solve2(FILE *file, int my_len);

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

    /** get len of my tic and win tic */
    DynString *str = NULL;
    dyn_string_get_file_line(&str, file);
    const char * const s = get_str_arr(str);
    int i, my_len = 0;
    for (i = 8; s[i] != '|'; ++i);;

    for (int j = i; j < get_lengthof(str) ; ++j){
        if (isdigit(s[j])){
            int num_width = str_num_width(s + j, get_lengthof(str) - j);
            ++my_len;
            j += num_width;
        }
    }
    rewind(file);

    uint32_t points = solve(file, my_len);
    rewind(file);
    uint32_t points2 = solve2(file, my_len);
    fclose(file);

    printf("POINTS::\n");
    printf("Part 1: %d\n", points);
    printf("Part 2: %d\n", points2);

    return 0;
}

uint32_t solve(FILE *file, int my_len){
    uint32_t my_set[my_len];
    int sum = 0;
    int n = 0;

    DynString *str = NULL;
    while (dyn_string_get_file_line(&str, file)){
        
        uint32_t win_hashmap[100] = {0};
        const char * const s = get_str_arr(str);
        int i = 4;
        while (s[i] != ':') ++i;
        
        int xcount = 0;
        for (; s[i] != '|'; ++i){
            if (isdigit(s[i])){
                int num_width = str_num_width(s + i, get_lengthof(str) - i);
                int x = strtoint(s + i, num_width);
                win_hashmap[x] = x;
                i += num_width;
            }
        }
        for (int j = i + 2; j < get_lengthof(str); ++j){
            if (isdigit(s[j])){
                int num_width = str_num_width(s + j, get_lengthof(str) - j);
                int x = strtoint(s + j, num_width);
                my_set[xcount] = x;
                ++xcount;
                j += num_width;
           }
       }
       for (int k = 0; k < my_len; ++k){
           if (win_hashmap[my_set[k]])
               ++n;
       }
       sum += n ? 1 << (n - 1): 0;
       n = 0;
       dyn_string_kill(str);
    }
    dyn_string_kill(str);
    
    return sum;
}

/* part 1 hand holds part 2 so this is largely the same */
uint32_t solve2(FILE *file, int my_len){
    uint32_t card_hashmap[FILE_LENGTH] = {0};
    uint32_t my_set[my_len];
    int n  = 0;
    int card = 0;
    int sum  = 0;
    int cc = 0;

    DynString *str = NULL;
    while (dyn_string_get_file_line(&str, file)){
        ++card_hashmap[cc++];

        uint32_t win_hashmap[100] = {0};
        const char * const s = get_str_arr(str);
        int i = 4;
        while (s[i] != ':') ++i;
        
        int xcount = 0;
        for (; s[i] != '|'; ++i){
            if (isdigit(s[i])){
                int num_width = str_num_width(s + i, get_lengthof(str) - i);
                int x = strtoint(s + i, num_width);
                win_hashmap[x] = x;
                i += num_width;
            }
        }
        for (int j = i + 2; j < get_lengthof(str); ++j){
            if (isdigit(s[j])){
                int num_width = str_num_width(s + j, get_lengthof(str) - j);
                int x = strtoint(s + j, num_width);
                my_set[xcount] = x;
                ++xcount;
                j += num_width;
           }
       }
       for (int k = 0; k < my_len; ++k){
           if (win_hashmap[my_set[k]])
               ++n;
       }

       for (int q = card + 1; q <= (card + n); ++q)
           card_hashmap[q] += card_hashmap[card];

       n = 0;
       dyn_string_kill(str);
       ++card;
    }
    dyn_string_kill(str);
    
    for (int i = 0; i < card; ++i)
        sum += card_hashmap[i];

    return sum;
}
