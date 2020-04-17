//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include <windows.h>
#include "input_output.h"

void print_board(square board[8][8])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    printf("\n    **********  THE BOARD  **********  \n");
    printf("  0     1    2    3    4    5    6    7   \n");
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].type == VALID)
            {
                if(board[i][j].stack == NULL) {
                    printf("|    ");
                }
                    else
                    {
                        if(board[i][j].stack->p_color == GREEN) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                            printf("| G %d", board[i][j].num_pieces);
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                        }
                        else {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                            printf("| R %d", board[i][j].num_pieces);
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                        }
                    }
                }
            else
                printf("| -  ");
            }
        printf("|");
        printf("  %d \n", i);
    }
}


