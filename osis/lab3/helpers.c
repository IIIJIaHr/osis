#include "helpers.h"

inline int strlength(char* str) {
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}
