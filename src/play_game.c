//
// Created by camek on 06/04/2020.
//


#include <stdio.h>
#include "play_game.h"
#include "player_movement.h"

void play_game(player player1, player player2, square board[8][8])
{
    int topIsRed, topIsGreen;
    int x = 0;
    char line[20];

    do {
        topIsRed = 0;
        topIsGreen = 0;
        for (int i = 0; i < 8; i++) { // checks through the board tp see if win conditions have been made
            for (int j = 0; j < 8; j++) {
                if(board[i][j].type == INVALID) // need this line to avoid crashes as not every square has a stack
                    continue;
                else if(board[i][j].num_pieces == 0) // need this line to avoid crashes as not every square has a stack
                    continue;
                else if(board[i][j].stack->p_color == RED) // if there is a red stack available to move sets red to 1
                    topIsRed = 1;
                else if(board[i][j].stack->p_color == GREEN) // if there is a green stack available to move sets green to 1
                    topIsGreen = 1;
                else
                    continue;
            }
        }

        if((topIsRed == 0 || topIsGreen == 0) && player1.pieces_captured == 0)
        {
            finish_screen(player2, x);
            break;
        }

        int move = 0;
        x++;

        printf("Turn : %d\nPlayer 1 : %s", x, player1.player_name);
        printf("You have captured %d pieces\n", player1.pieces_captured);
        printf("You have destroyed %d pieces\n", player1.pieces_destroyed);

        if(player1.pieces_captured > 0) {
            printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other ke to move a stack: ", player1.pieces_captured);
            fgets(line, sizeof(line), stdin);
            sscanf(line, "%d", &move);
        }
        if(move == 1)
            position_captured_piece(&player1, board);
        else
            move_piece(&player1, board);

        topIsRed = 0;
        topIsGreen = 0;
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
            finish_screen(player1, x);
            break;
        }

        printf("Turn : %d\nPlayer 2 : %s", x, player2.player_name);
        printf("You have captured %d pieces\n", player2.pieces_captured);
        printf("You have destroyed %d pieces\n", player2.pieces_destroyed);

        move = 0;

        if(player2.pieces_captured > 0) {
            printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other key to move a stack: ", player2.pieces_captured);
            fgets(line, sizeof(line), stdin);
            sscanf(line, "%d", &move);
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
