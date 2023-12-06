#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "dyn_string.h"

/* go through map like you're filtering an image */

#define GROW 64

/* solutions */
uint32_t solve(int height, DynString *map[height]);
uint32_t solve2(int height, DynString *map[height]);

/* helpers */
int strtoint(const char * const s, int len);
int str_num_width(const char *s, int max_step);
int probe(const char * const s, int idx, int len);

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
    
    int height = 0, size = GROW;
    DynString **dstr = malloc(GROW * sizeof(*dstr));
    while (dyn_string_get_file_line(dstr + height, file)){
        ++height;
        if (height == size){
            dstr = realloc(dstr, (GROW + size) * sizeof(*dstr));
            size += GROW;
        }
    }

    uint32_t sum  =  solve(height, dstr);
    uint32_t sum2 = solve2(height, dstr);

    printf("sum from engine schematic::\n");
    printf("Part 1: %d\n", sum);
    printf("Part 2: %d\n", sum2);

    for (int i = 0; i < height + 1; ++i)
        dyn_string_kill(dstr[i]);
    free(dstr);

    return 0;
}

uint32_t solve(int height, DynString *map[height]){
    const int width = get_lengthof(*map);
    int sum = 0;
    for (int i = 0; i < height; ++i){
        const char * const s = get_str_arr(map[i]);
        for (int j = 0; j < width; ++j){
            int num_width = 0;

            int x, y = height - i - 1; 

            if (isdigit(s[j])){
                num_width = str_num_width(s + j, width - j);
                x = j + num_width;
                int travel = 2 * num_width + 5;
                
                for (int k = 0; k <= travel; ++k){
                    if (x >= 0 && x < width && y >= 0 && y < height)
                       if (get_str_arr(map[height - y - 1])[x] != '.'){
                           sum += strtoint(s + j, num_width);
                           break;
                       }
                    /** change course */
                    if (k == 0){
                        y += 1;
                        continue;
                    }
                    if ((k - 1) <= num_width){
                        x -= 1;
                        continue;
                    }
                    if ((k - 1) >= num_width && k < (1 + num_width + 3)){
                        y -= 1;
                        continue;
                    }
                    if ((1 + num_width + 3) <= k){
                        x += 1;
                        continue;
                    }
                }
                j += num_width;
            }
        }
    }
    return sum;
}

uint32_t solve2(int height, DynString *map[height]){
    const int width = get_lengthof(*map);
    int sum = 0;
    for (int i = 0; i < height; ++i){
        const char * const s = get_str_arr(map[i]);
        
        for (int j = 0; j < width; ++j){

            if (s[j] == '*'){
                int x = j, y = height - i - 1; 
                int counter = 0, nums[2];
                bool y_same = true, wait_for_sym = false, broke_rule = false;
                
                for (int k = 0; k < 9; ++k){
                
                    if (x >= 0 && x < width && y >= 0 && y < height){
                        const char * const q = get_str_arr(map[height - y - 1]);
                    
                    /* you have to wait for a symbol <-> you are on the same row */    
                        if (wait_for_sym == y_same)
                            switch (k % 4) {
                            case 0:
                            case 3: if isdigit(q[x]) broke_rule = true; break;
                            default: broke_rule = false; break;
                            }

                        if (isdigit(q[x]) && !broke_rule){
                            int idx = probe(q, x, get_lengthof(map[height - y - 1]));
                            int num_width = str_num_width(q + idx, width - idx);
                            nums[counter] = strtoint(q + idx, num_width);
                            ++counter;
                            
                            switch (k % 4) {
                            case 2:
                            case 3: wait_for_sym = true; break;
                            default: break;
                            }
                        }
                        if (counter == 2){
                            sum += nums[0] * nums[1];
                            break;
                        }
                        switch (k % 4) {
                        case 3:
                        case 7: if (!isdigit(q[x])) wait_for_sym = false; break;
                        default: break;
                        }
                    }
                    switch (k) {
                    case 0: x += 1;
                        break;
                    case 1: y += 1;
                        y_same = false;
                        wait_for_sym = false;
                        break;
                    case 2:
                    case 3: x -= 1;
                        y_same = true;
                        break;
                    case 4:
                    case 5: y -= 1;
                        y_same = false;
                        wait_for_sym = false;
                        break;
                    case 6:
                    case 7: x += 1;
                        y_same = true;
                        break;
                    default: break;
                    }
                }
            }
        }
    }
    return sum;
}

int strtoint(const char * const s, int len){
    int num = 0;
    for (int i = 0; i < len; ++i)
        num = num * 10 + (s[i] - '0');
    return num;
}

int str_num_width(const char * const s, int max_step){
    int i, j;
    for (i = 0, j = 0;
         isdigit(s[j]) && j < max_step;
         i += (isdigit(s[j]) != 0), ++j
         );
    return i;
}

/* find out where the number begins */
int probe(const char * const s, int idx, int len){
    int i;
    if (idx == 0) return idx;
    if (idx == len - 1 || isdigit(s[idx - 1])){
        for (i = idx; i >= 0; --i)
            if (!isdigit(s[i]))
                break;
        return i + 1;
    }
    return idx;
}
