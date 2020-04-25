//
// Created by camek on 06/04/2020.
//


#include <stdio.h>
#include <stdlib.h>
#include "play_game.h"
#include "player_movement.h"
#include "OS_functions.h"

void play_game(player player1, player player2, square board[8][8])
{
    int topIsRed, topIsGreen, accept;
    int turns = 0;
    char line[20];

    do {
        topIsRed = 0;
        topIsGreen = 0;
        accept = 0;
        // Player 1
        // checks through the board to see if a stack can be moved. If not win conditions may have been met depending on number of captured pieces
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // If square is invalid continue
                if(board[i][j].type == INVALID)
                    continue;
                // If no pieces on square continue
                else if(board[i][j].num_pieces == 0)
                    continue;
                // if there is a red stack available to move we know red player can move
                else if(board[i][j].stack->p_color == RED)
                    topIsRed = 1;
                // if there is a green stack available to move we know green player can move
                else if(board[i][j].stack->p_color == GREEN)
                    topIsGreen = 1;
                else
                    continue;
            }
        }

        // If the player 1 cant move before turn then we pass player 2 into win screen function
        if(topIsRed == 0 && player1.pieces_captured == 0)
        {
            finish_screen(player2, turns, board);
            break;
        }

        int move = 0;
        turns++; // Counts the number of turns each player makes

        if(player1.player_color == RED)
            red();
        else
            green();

        printf("\n\n\n\nTurn : %d\nPlayer 1 : %s", turns, player1.player_name);
        printf("You have captured %d pieces\n", player1.pieces_captured);
        printf("You have destroyed %d pieces\n", player1.pieces_destroyed);

        /* If a player has no stack to move but has pieces captured this forces the player to place a capture piece. Implemented this function to stop players from saying they
        wanted to move a stack when no stack was available so would cause a dead screen with nothing to do causing the game to be in an unplayable game state */
        if ((player1.player_color == RED && topIsRed == 0 && player1.pieces_captured > 0) || (player1.player_color == GREEN && topIsGreen == 0 && player1.pieces_captured > 0)) {
            printf("There is no available stack to move. You must place one of your %d captured pieces\n", player1.pieces_captured);
            position_captured_piece(&player1, board);
            accept = 1;
        }

        // If player 1 has pieces captured they can choose to place a captured piece onto the board
        else if (player1.pieces_captured > 0) {
            printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other key to move a stack: ", player1.pieces_captured);
            fgets(line, sizeof(line), stdin);
            sscanf(line, "%d", &move);
        }


        // If player already positioned captured piece we continue past the other two if statements as we do not want to move again
        if(accept != 1) {
            // If player pressed 1 to place captured piece we call that function
            if(move == 1)
                position_captured_piece(&player1, board);
            // Otherwise they move there own stack
            else
                move_piece(&player1, board);
        }


        topIsRed = 0;
        topIsGreen = 0;
        accept = 0;
        // Player 2
        // Again check through board to see if stack can be moved
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if(board[i][j].type == INVALID)
                    continue;
                else if(board[i][j].num_pieces == 0)
                    continue;
                if(board[i][j].stack->p_color == RED)
                    topIsRed = 1;
                else if(board[i][j].stack->p_color == GREEN)
                    topIsGreen = 1;
                else
                    continue;
            }
        }

        // If the player 2 cant move before turn then we pass player 1 into win screen function
        if((topIsRed == 0 || topIsGreen == 0) && player2.pieces_captured == 0)
        {
            finish_screen(player1, turns, board);
            break;
        }

        if(player2.player_color == RED)
            red();
        else
            green();

        printf("\n\n\n\nTurn : %d\nPlayer 2 : %s", turns, player2.player_name);
        printf("You have captured %d pieces\n", player2.pieces_captured);
        printf("You have destroyed %d pieces\n", player2.pieces_destroyed);

        move = 0;

        /* If a player has no stack to move but has pieces captured this forces the player to place a capture piece. Implemented this function to stop players from saying they
        wanted to move a stack when no stack was available so would cause a dead screen with nothing to do causing the game to be in an unplayable game state */
        if ((player2.player_color == RED && topIsRed == 0 && player2.pieces_captured > 0) || (player2.player_color == GREEN && topIsGreen == 0 && player2.pieces_captured > 0)) {
            printf("There is no available stack to move. You must place one of your %d captured pieces\n", player2.pieces_captured);
            position_captured_piece(&player2, board);
            accept = 1;
        }

        // If player 2 has pieces captured they can choose to place a captured piece onto the board
        else if (player2.pieces_captured > 0) {
            printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other key to move a stack: ", player2.pieces_captured);
            fgets(line, sizeof(line), stdin);
            sscanf(line, "%d", &move);
        }


        // If player already positioned captured piece we continue past the other two if statements as we do not want to move again
        if(accept != 1) {
            // If player pressed 1 to place captured piece we call that function
            if(move == 1)
                position_captured_piece(&player2, board);
            // Otherwise they move there own stack
            else
                move_piece(&player2, board);
        }

    } while((topIsRed == 1 && topIsGreen == 1) || accept == 1);
}

void finish_screen(player winner, int turns, square board[8][8]) {
    printf("\n\n\n\n ************** GAME OVER **************\n");
    printf("Player : %s won!\n", winner.player_name); // Prints the winners name
    printf("It took you %d turns to win\n", turns); // Prints the total turns it took to win

    if(winner.player_color == RED)
        printf("%s won as the red color!\n", winner.player_name); // Prints the winners color
    else
        printf("%s won as the green color!\n", winner.player_name); // Prints the winners color

    printf("You finished the game with %d captured pieces\n", winner.pieces_captured); // Prints the number of pieces the player has by the end of the game
    printf("You finished the game destroying %d pieces\n", winner.pieces_destroyed); // Prints the number of pieces a player destroyed

    // Frees up the memory used from the stacks
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j].type == INVALID)
                continue;
            else if(board[i][j].num_pieces > 1)
                free_memory(&board[i][j]);
        }
    }
}

void free_memory(square *pieces) {
    piece *curr = pieces->stack; 
    while(curr != NULL) {
        free(curr);
        curr = curr->next;
    }
}
