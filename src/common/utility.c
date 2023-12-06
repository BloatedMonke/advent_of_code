#include <ctype.h>
#include "utility.h"

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