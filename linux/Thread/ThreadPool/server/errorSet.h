#ifndef ERROR_SET_H
#define ERROR_SET_H

#include <stdio.h>
#include <stdlib.h>

#define ARGS_CHECK(argc, num, str) \
    do {                           \
        if ((argc) != (num)) {     \
            printf("%s\n", (str)); \
            exit(1);               \
        }                          \
    } while (0)

#define ERROR_CHECK(ret, val, str) \
    do {                           \
        if ((ret) == (val)) {      \
            perror((str));         \
            exit(1);               \
        }                          \
    } while (0)

#endif