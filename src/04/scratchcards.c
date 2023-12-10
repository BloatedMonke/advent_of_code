#include <ctype.h>
#include <stdio.h>
#include "dyn_string.h"
#include "utility.h"

#ifndef MAX_CARDS
#define MAX_CARDS 198
#endif
#ifndef MAX_LEN
#define MAX_LEN 25
#endif

struct solution {
    uint32_t part1;
    uint32_t part2;
};

struct solution solve(FILE *file);

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

    struct solution points = solve(file);
    fclose(file);

    printf("POINTS::\n");
    printf("Part 1: %d\n", points.part1);
    printf("Part 2: %d\n", points.part2);

    return 0;
}

struct solution solve(FILE *file){
    int n = 0;
    uint32_t my_set[MAX_LEN];
    
    int sum1 = 0;
    
    uint32_t card_hashmap[MAX_CARDS] = {0};    
    int card = 0;
    int cc = 0;
    
    DynString *str = NULL;
    while (dyn_string_get_file_line(&str, file)){
        ++card_hashmap[cc++];

        uint32_t win_hashmap[100] = {0};
        const char * const s = get_str_arr(str);
        
        int i = 4;
        while (s[i] != ':') ++i;
        
        for (; s[i] != '|'; ++i)
            if (isdigit(s[i])){
                int num_width = str_num_width(s + i, get_lengthof(str) - i);
                int x = strtoint(s + i, num_width);
                win_hashmap[x] = x;
                i += num_width;
            }
        int xcount = 0;
        for (int j = i + 2; j < get_lengthof(str); ++j){
            if (isdigit(s[j])){
                int num_width = str_num_width(s + j, get_lengthof(str) - j);
                int x = strtoint(s + j, num_width);
                my_set[xcount] = x;
                ++xcount;
                j += num_width;
           }
        }
        for (int k = 0; k < xcount; ++k){
           if (win_hashmap[my_set[k]])
               ++n;
        }
        sum1 += n ? 1 << (n - 1): 0;
       
        for (int q = card + 1; q <= (card + n); ++q)
            card_hashmap[q] += card_hashmap[card];
        ++card;
        n = 0;
        dyn_string_kill(str);
    }
    dyn_string_kill(str);

    int sum2 = 0;
    for (int i = 0; i < card; ++i)
        sum2 += card_hashmap[i];
    
    return (struct solution){.part1 = sum1, .part2 = sum2};
}
