//
// Created by camek on 06/04/2020.
//


#include <stdio.h>
#include "play_game.h"
#include "player_movement.h"

void play_game(player player1, player player2, square board[8][8])
{
    int topIsRed, topIsGreen;
    int j = 0;
    do {
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

        if(topIsRed == 0 || topIsGreen == 0)
        {
            printf("Winner");
            break;
        }

        int move = 0;
        j++;

        printf("Turn : %d\nPlayer 1 : %s", j, player1.player_name);
        printf("You have captured %d pieces\n", player1.pieces_captured);
        printf("You have destroyed %d pieces\n", player1.pieces_destroyed);

        if(player1.pieces_captured > 0) {
            printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other number to move a stack: ", player1.pieces_captured);
            scanf("%d", &move);
        }
        if(move == 1)
            position_captured_piece(&player1, board);
        else
            move_piece(&player1, board);

        printf("Turn : %d\nPlayer 2 : %s", j, player2.player_name);
        printf("You have captured %d pieces\n", player2.pieces_captured);
        printf("You have destroyed %d pieces\n", player2.pieces_destroyed);

        move = 0;

        if(player2.pieces_captured > 0) {
            printf("\nYou have %d pieces captured. Press 1 to place a captured piece on the board, press any other number to move a stack: ", player2.pieces_captured);
            scanf("%d", &move);
        }
        if(move == 1)
            position_captured_piece(&player2, board);
        else
            move_piece(&player2, board);

    } while(topIsRed == 1 && topIsGreen == 1);
}
