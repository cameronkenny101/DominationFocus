//
// Created by camek on 17/04/2020.
//

#include <stdio.h>
#include "OS_functions.h"

#ifdef _WIN32
#include <windows.h>

// Function to print the color of green
void green(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}
#else

// Function to print the color green for other operating systems
void green(void) {
    printf("\x1B[32m");
}
#endif

#ifdef _WIN32

// Function to print the color red
void red(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}
#else

// Function to print the color red for other opertating systems
void red(void) {
    printf("\x1B[31m");
}
#endif

#ifdef _WIN32

// Function to print the color blue
void blue(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}
#else

// Function to print the color blue on other operating systems
void blue(void) {
    printf("\x1B[34m");
}
#endif



