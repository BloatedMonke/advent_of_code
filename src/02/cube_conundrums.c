#include <ctype.h>
#include <stdio.h>
#include "dyn_string.h"
#include "utility.h"

uint32_t solve(FILE *file, int max_red, int max_green, int max_blue);
uint32_t solve2(FILE *file);

int main(int argc, const char *argv[])
{
    if (argc != 2){
        printf("Usage: %s INPUT_FILE.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file){
        printf("Could not find %s\n", argv[1]);
        fclose(file);
        return 2;
    }

    uint32_t sum = solve(file, 12, 13, 14);
    rewind(file);
    uint32_t sum2 = solve2(file);
    fclose(file);

    printf("sum of the possible game IDs::\n");
    printf("Part 1: %d\n", sum);
    printf("sum of the powers of the sets::\n");
    printf("Part 2: %d\n", sum2);

    return 0;
}

enum {red = 0, green, blue};

uint32_t solve(FILE *file, int max_red, int max_green, int max_blue){
    int vec[3] = {0};

    const char separator = ';';
    uint32_t id_sum = 0;

    DynString *str = NULL;
    while (dyn_string_get_file_line(&str, file)){
        /* pad with extra sep */
        dyn_string_append(&str, ';');

        const char * const s = get_str_arr(str);
        int width = str_num_width(s + 5, get_lengthof(str) - 5);
        int id = strtoint(s + 5, width);
        int num = 0;
        for (int i = 7 + width; i < get_lengthof(str); ++i){
            if (isdigit(s[i])){
                int num_width = str_num_width(s + i, get_lengthof(str) - i);
                num = strtoint(s + i, num_width);
                i += num_width + 1;
            }

            switch (s[i]) {
            case 'r':
                vec[red] = num;
                i += 3;
                break;
            case 'g':
                vec[green] = num;
                i += 5;
                break;
            case 'b':
                vec[blue] = num;
                i += 4;
                break;
            default: break;
            }

            if (vec[red] > max_red || vec[green] > max_green || vec[blue] > max_blue){
                vec[red] = 0;
                vec[green] = 0;
                vec[blue] = 0;
                id = 0;
                break;
            }

            if (s[i] == separator){
                vec[red] = 0;
                vec[green] = 0;
                vec[blue] = 0;
            }
        }
        id_sum += id;
        dyn_string_kill(str);
    }
    dyn_string_kill(str);
    return id_sum;
}

uint32_t solve2(FILE *file){
    int vec[3] = {0};
    int sum = 0;

    DynString *str = NULL;
    while (dyn_string_get_file_line(&str, file)){
        dyn_string_append(&str, ';');
        
        const char * const s = get_str_arr(str);
        int width = str_num_width(s + 5, get_lengthof(str) - 5);
        int num = 0;

        for (int i = 7 + width; i < get_lengthof(str); ++i){
            if (isdigit(s[i])){
                int num_width = str_num_width(s + i, get_lengthof(str) - i);
                num = strtoint(s + i, num_width);
                i += num_width + 1;
            }

            switch (s[i]) {
            case 'r':
                vec[red] = max(num, vec[red]);
                i += 3;
                break;
            case 'g':
                vec[green] = max(num, vec[green]);
                i += 5;
                break;
            case 'b':
                vec[blue] = max(num, vec[blue]);
                i += 4;
                break;
            default: break;
            }
        }
        sum += vec[red] * vec[green] * vec[blue];
        vec[red] = 0;
        vec[green] = 0;
        vec[blue] = 0;
        dyn_string_kill(str);
    }
    dyn_string_kill(str);

    return sum;
}
