#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <SDL3/SDL.h>

#if __WIN32
#define CLEAR system("cls")
#define SLEEP(secs) {                                        \
    char buf[32] = {0};                                      \
    sprintf(buf, "timeout /t %d /nobreak > nul", (int)secs); \
    system(buf);                                             \
}
#define DELETE_FILE(file) {            \
    char str[32] = {0};                \
    snprintf(str, 32, "del %s", file); \
    system(str);                       \
}
#elif __APPLE__
#define CLEAR system("clear")
#define SLEEP(secs) {                    \
    char str[32] = {0};                  \
    snprintf(str, 32, "sleep %f", secs); \
    system(str);                         \
}
#define DELETE_FILE(file) {           \
    char str[32] = {0};               \
    snprintf(str, 32, "rm %s", file); \
    system(str);                      \
}
#endif

#define WIN_W 1280
#define WIN_H 720

#define CHECK_RANGE(in, r1, r2) (in > r1 && in < r2) ? true : false
#define CHAR2INT(x) x - '0'
#define INT2CHAR(x) x + '0'
#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])

#endif
