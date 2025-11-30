// is_same.h
#ifndef _IS_SAME_H
#define _IS_SAME_H
#include <stdbool.h>
#include <string.h>

static inline bool is_same(const char* s1, const char *s2) {
    bool cmp;

    if(sizeof(s1) != sizeof(s2)) { return false; }

    for(int i = 0; i < sizeof(s1); i++) {
        cmp = (s1[i] == s2[i] ? true : false);
        if(cmp == false) { break; }
    }

    return cmp;
}

#endif
