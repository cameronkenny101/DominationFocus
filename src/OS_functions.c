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
void green(void) {
    printf("\x1B[32m");
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
void red(void) {
    printf("\x1B[31m");
}
#endif

#ifdef _WIN32
#include <windows.h>
void blue(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}
#else
void blue(void) {
    printf("\x1B[34m");
}
#endif



