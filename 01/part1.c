#include <stdio.h>
#include <ctype.h>

typedef enum bool {
    false = 0,
    true
}
bool;

int main(int argc, const char *argv[]){
    if (argc != 2){
        printf("Usage: %s INPUT.txt\n", argv[0]);
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    if (!input){
        printf("Could not find %s\n", argv[1]);
        return 2;
    }
    
    char c;
    int sum = 0;
    bool you_are_the_first = true;
    while (fread(&c, sizeof(c), 1, input)){
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
    fclose(input);
    
    printf("sum of all calibration values: %d\n", sum);
    return 0;
}