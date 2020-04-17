//
// Created by camek on 17/04/2020.
//

#include <stdio.h>
#include "OS_functions.h"

#ifdef _WIN32
#include <windows.h>
    void green(void) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}
#else
#define GRN   "\x1B[32m"
    void green(void) {
        printf(GRN);
}
#endif

#ifdef _WIN32
#include <windows.h>
void red(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}
#else
#define RED   "\x1B[31m"
void red(void) {
    printf(RED);
}
#endif

#ifdef _WIN32
#include <windows.h>
void clear(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}
#else
#define BLU   "\x1B[34m"
void clear(void) {
    printf("BLU")
}
#endif



