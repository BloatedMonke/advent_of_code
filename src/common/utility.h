#ifndef _UTILITY_H_
#define _UTILITY_H_

#define max(a, b) ((a) > (b) ? (a): (b))

int strtoint(const char * const s, int len);
int str_num_width(const char * const s, int max_step);

#endif