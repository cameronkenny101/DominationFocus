//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include "input_output.h"

void print_board(square board[8][8])
{
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
                            printf("| G %d", board[i][j].num_pieces);
                        }
                        else
                            printf("| R %d", board[i][j].num_pieces);
                    }
                }
            else
                printf("| -  ");
            }
        printf("|");
        printf("  %d \n", i);
    }
}


