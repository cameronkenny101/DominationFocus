//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"



void initialize_players(player *player1, player *player2){
    int color = 0;
    int playerNumber = 0;
    char line[20];

    printf("Please enter name of Player %d : ", ++playerNumber); // Takes in Players 1 name
    fgets(player1->player_name, 50, stdin);

    printf("\nEnter 1 to choose red, enter any other number to be green : ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &color);

    if(color == 1) {
        player1->player_color = RED;
        printf("\nPlayer 1 choose Red!\n");
    }
    else {
        player1->player_color = GREEN;
        printf("\nPlayer 1 choose Green!\n");
    }

    printf("\nPlease enter name of Player %d : ", ++playerNumber);
    fgets(player2->player_name, 49, stdin);

    if(player1->player_color == RED) {
        player2->player_color = GREEN;
        printf("\nPlayer 2 is Green!\n");
    }
    else {
        player2->player_color = RED;
        printf("\nPlayer 2 is Red!\n");
    }

    player1->pieces_captured = 0;
    player1->pieces_destroyed = 0;
    player2->pieces_captured = 0;
    player2->pieces_destroyed = 0;
}

void set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->bottom = NULL;
s->num_pieces = 0;
}

void set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->bottom = NULL;

s->num_pieces = 0;
}

void set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
s->bottom = s->stack;

}

void set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
s->bottom = s->stack;
}

void initialize_board(square board[8][8]) {
    for(int i=0; i< 8; i++){
        for(int j=0; j< 8; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7))) {
                set_invalid(&board[i][j]);
                board[i][j].num_pieces = 0;
            }

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7) {
                    set_empty(&board[i][j]);
                    board[i][j].num_pieces = 0;
                }
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) || (i%2 == 0 && (j == 3 || j==4))) {
                        set_red(&board[i][j]);
                        board[i][j].num_pieces = 1;
                    }

                        //green squares
                    else
                    {
                        set_green(&board[i][j]);
                        board[i][j].num_pieces = 1;
                    }
                }
            }
        }
    }
}


