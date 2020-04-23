//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"
#include "OS_functions.h"


// Initalizes the player with user input
void initialize_players(player *player1, player *player2){
    int color = 0;
    int playerNumber = 0;
    char line[20];

    blue();


    printf("          __          ________ _      _____ ____  __  __ ______   _______ ____  \n"
                   "          \\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____| |__   __/ __ \\  \n"
                   "           \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__       | | | |  | | \n"
                   "            \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|      | | | |  | |  \n"
                   "             \\  /\\  /  | |____| |___| |___| |__| | |  | | |____     | | | |__| |  \n"
                   "              \\/  \\/   |______|______\\_____\\____/|_|  |_|______|    |_|  \\____/  \n\n\n\n"
                   "             _____   ____  __  __ _____ _   _       _______ _____ ____  _   _    \n"
                   "            |  __ \\ / __ \\|  \\/  |_   _| \\ | |   /\\|__   __|_   _/ __ \\| \\ | |   \n"
                   "            | |  | | |  | | \\  / | | | |  \\| |  /  \\  | |    | || |  | |  \\| |   \n"
                   "            | |  | | |  | | |\\/| | | | | . ` | / /\\ \\ | |    | || |  | | . ` |    \n"
                   "            | |__| | |__| | |  | |_| |_| |\\  |/ ____ \\| |   _| || |__| | |\\  |   \n"
                   "            |_____/ \\____/|_|  |_|_____|_| \\_/_/    \\_\\_|  |_____\\____/|_| \\_|   \n\n\n");

    // Takes in Players 1 name
    printf("Please enter name of Player %d : ", ++playerNumber);
    fgets(player1->player_name, 30, stdin);

    // Takes in user color with number input. Use fgets and sscanf as if a letter is entered it clears it out of the buffer, meaning no infinite loops
    printf("\n\nEnter 1 to choose red, enter any other number to be green : ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &color);

    // If users enter 1 they are assigned to the red color
    if(color == 1) {
        player1->player_color = RED;
        red();
        printf("\nPlayer 1 choose Red!\n");
        blue();
    }
    // If user enters any other key they are assigned to green
    else {
        player1->player_color = GREEN;
        green();
        printf("\nPlayer 1 choose Green!\n");
        blue();
    }

    // Takes in Player 2 name
    printf("\nPlease enter name of Player %d : ", ++playerNumber);
    fgets(player2->player_name, 30, stdin);

    // Assigns player color based on choice Player 1 made
    if(player1->player_color == RED) {
        green();
        player2->player_color = GREEN;
        printf("\nPlayer 2 is Green!\n");
        blue();
    }
    else {
        red();
        player2->player_color = RED;
        printf("\nPlayer 2 is Red!\n");
        blue();
    }

    // Initilizes the number of pieces captured and destroyed to 0 for each player
    player1->pieces_captured = 0;
    player1->pieces_destroyed = 0;
    player2->pieces_captured = 0;
    player2->pieces_destroyed = 0;
}

// Sets a square to be invalid with no pieces on it
void set_invalid(square * s) {
s->type = INVALID;
s->stack = NULL;
s->bottom = NULL;
s->num_pieces = 0;
}

// Sets a square valid but with no pieces on it
void set_empty(square * s) {
s->type = VALID;
s->stack = NULL;
s->bottom = NULL;
s->num_pieces = 0;
}

// Sets a square valid and with one green piece on it
void set_green(square * s) {
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
s->bottom = s->stack;
}

// Sets a square valid and with one red piece on it
void set_red(square * s) {
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
s->bottom = s->stack;
}

// Initializes the board with the set functions
void initialize_board(square board[8][8]) {
    for(int i=0; i< 8; i++){
        for(int j=0; j< 8; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7))) {
                set_invalid(&board[i][j]);
            }

            else{
                // squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7) {
                    set_empty(&board[i][j]);
                }
                else{
                    // squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) || (i%2 == 0 && (j == 3 || j==4))) {
                        set_red(&board[i][j]);
                    }
                    // green squares
                    else {
                        set_green(&board[i][j]);
                    }
                }
            }
        }
    }
}


