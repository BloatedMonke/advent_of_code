#ifndef _DYN_STRING_H
#define _DYN_STRING_H

#include <stdint.h>

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

/* "Methods" */
DynString *dyn_string_birth(void);
void dyn_string_append(DynString **, char c);
void dyn_string_kill(DynString *);
bool dyn_string_get_file_line(DynString **dstr, FILE *file);
void dyn_string_print(DynString *str);
void dyn_string_part_print(DynString *str, int idx);

#endif
