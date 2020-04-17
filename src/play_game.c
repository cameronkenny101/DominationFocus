//
// Created by camek on 06/04/2020.
//


#include <stdio.h>
#include "play_game.h"
#include "player_movement.h"

void play_game(player player1, player player2, square board[8][8])
{
    int topIsRed, topIsGreen;
    int turns = 0;
    char line[20];

    do {
        topIsRed = 0;
        topIsGreen = 0;
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
            finish_screen(player2, turns);
            break;
        }

        int move = 0, accept = 0;
        turns++; // Counts the number of turns each player makes

        printf("Turn : %d\nPlayer 1 : %s", turns, player1.player_name);
        printf("You have captured %d pieces\n", player1.pieces_captured);
        printf("You have destroyed %d pieces\n", player1.pieces_destroyed);

        while(accept == 0) {
            /* If a player has no stack to move but has pieces captured this forces the player to place a capture piece. Implemented this function to stop players from saying they
            wanted to move a stack when no stack was available so would cause a dead screen with nothing to do causing the game to be in an unplayable game state */
            if ((player1.player_color == RED && topIsRed == 0 && player1.pieces_captured > 0) || (player1.player_color == GREEN && topIsGreen == 0 && player1.pieces_captured > 0)) {
                printf("There is no available stack to move. You must place one of your %d captured pieces", player1.pieces_captured);
                position_captured_piece(&player1, board);
                break;
            }

            // If player 1 has pieces captured they can choose to place a captured piece onto the board
            if (player1.pieces_captured > 0) {
                printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other ke to move a stack: ", player1.pieces_captured);
                fgets(line, sizeof(line), stdin);
                sscanf(line, "%d", &move);
                accept = 1;
            }
        }

        // If player presses 1 to place captured piece we call that function
        if(move == 1)
            position_captured_piece(&player1, board);
        // Otherwise they move there own stack
        else
            move_piece(&player1, board);

        topIsRed = 0;
        topIsGreen = 0;
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

        if((topIsRed == 0 || topIsGreen == 0) && player2.pieces_captured == 0)
        {
            finish_screen(player1, turns);
            break;
        }

        printf("Turn : %d\nPlayer 2 : %s", turns, player2.player_name);
        printf("You have captured %d pieces\n", player2.pieces_captured);
        printf("You have destroyed %d pieces\n", player2.pieces_destroyed);

        move = 0, accept = 0;

        while(accept == 0) {
            /* If a player has no stack to move but has pieces captured this forces the player to place a capture piece. Implemented this function to stop players from saying they
            wanted to move a stack when no stack was available so would cause a dead screen with nothing to do causing the game to be in an unplayable game state */
            if ((player1.player_color == RED && topIsRed == 0 && player1.pieces_captured > 0) || (player1.player_color == GREEN && topIsGreen == 0 && player1.pieces_captured > 0)) {
                printf("There is no available stack to move. You must place one of your %d captured pieces", player1.pieces_captured);
                position_captured_piece(&player1, board);
                break;
            }

            // If player 1 has pieces captured they can choose to place a captured piece onto the board
            if (player1.pieces_captured > 0) {
                printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other ke to move a stack: ", player1.pieces_captured);
                fgets(line, sizeof(line), stdin);
                sscanf(line, "%d", &move);
                accept = 1;
            }
        }

        if(move == 1)
            position_captured_piece(&player2, board);
        else
            move_piece(&player2, board);

    } while(topIsRed == 1 && topIsGreen == 1);
}
void finish_screen(player winner, int turns)
{
    printf("\n\n\n\n ************** GAME OVER **************\n");
    printf("Player : %s won!\n", winner.player_name);
    printf("It took you %d turns to win\n", turns);

    if(winner.player_color == RED)
        printf("%s won as the red color!\n", winner.player_name);
    else
        printf("%s won as the green color!\n", winner.player_name);

    printf("You finished the game with %d captured pieces", winner.pieces_captured);
    printf("You finished the game destroying %d pieces", winner.pieces_destroyed);


}
