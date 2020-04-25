//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include "input_output.h"
#include "OS_functions.h"

// Function for printing board
void print_board(square board[8][8])
{
    blue(); // Text is set to blue
    printf("\n    **********  THE BOARD  **********  \n");
    printf("  0     1    2    3    4    5    6    7   \n"); // prints the index of the board
    // prints the pieces in the board
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL) {
                    printf("|    ");
                }
                    else {
                        if(board[i][j].stack->p_color == GREEN) {
                            green(); // Text is set to green
                            printf("| G %d", board[i][j].num_pieces);
                            blue(); // Text is set to blue
                        }
                        else {
                            red(); // Text is set to red
                            printf("| R %d", board[i][j].num_pieces);
                            blue(); // Text is set to blue
                        }
                    }
                }
            else
                printf("| -  ");
            }
        printf("|");
        printf("  %d \n", i); // prints the index vertically
    }
}


