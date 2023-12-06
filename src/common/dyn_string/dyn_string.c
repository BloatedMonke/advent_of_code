#include <stdio.h>
#include <stdlib.h>

#include "dyn_string.h"

/* A somewhat reasonable grow size */
#define GROW 64

#if defined(_MSC_VER) || defined(__MINGW32__)
#define EOL '\r'
#else
#define EOL '\n'
#endif

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
    *dstr = dyn_string_birth();

    char c;
    bool break_loop = false;
    while (fread(&c, sizeof(c), 1, file)){
        if (c == EOL){
            break_loop = true;
            if (EOL == '\r')
                fseek(file, 1, SEEK_CUR);
            break;
        }
        dyn_string_append(dstr, c);
    }
    return break_loop;
}

void dyn_string_print(DynString *str){
    printf("str: \"");
    for (int i = 0; i < get_lengthof(str); ++i)
        putchar(get_str_arr(str)[i]);
    puts("\"");
}

void dyn_string_part_print(DynString *str, int idx){
    printf("str[%d:]: \"", idx);
    for (int i = idx; i < get_lengthof(str); ++i)
        putchar(get_str_arr(str)[i]);
    puts("\"");
}
