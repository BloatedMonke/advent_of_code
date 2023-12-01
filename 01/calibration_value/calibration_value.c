#include <stdio.h>
#include <ctype.h>

typedef enum bool {
    false = 0,
    true
}
bool;

int main(void){
    const char *input_file = "input.txt";
    FILE *input = fopen(input_file, "r");
    
    char c;
    int sum = 0;
    bool you_are_the_first = true;
    while (fread(&c, sizeof(char), 1, input)){
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
        }
    }
    
    printf("sum of all calibration values: %d\n", sum);
    return 0;
}