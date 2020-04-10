//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "player_movement.h"
#include "input_output.h"
#include "game_init.h"

void move_piece(player *players, square board[8][8])
{
    int cont = 0, row = 0, column = 0, accept, players_color = 0, square_color = 0;

    if(players->player_color == RED)
        players_color = 1;
    else
        players_color = 2;

    while(cont == 0)
    {
        printf("Please type the row of the piece you want to move : ");
        scanf("%d", &row);
        printf("Please type the column of the piece you want to move : ");
        scanf("%d", &column);

        if(row > 7 || row < 0 || column > 7 || column < 0)
            square_color = -1;
        else if(board[row][column].num_pieces == 0)
            square_color = 0;
        else if(board[row][column].stack->p_color == RED)
            square_color = 1;
        else
            square_color = 2;

        if(players_color != square_color)
        {
            printf("You selected a piece that doesnt belong to you. Please select again\n");
            continue;
        }

        printf("You selected the co-ordinates (row : %d , column : %d). Press 1 to continue or any other number to pick new co-ordinates : ", row, column);
        scanf("%d", &accept);
        if(accept == 1)
            cont = 1;
    }

    printf("8 is up, 4 is left, 6 is right, 2 is down\n");

    int correctPosition = 0, step, left = 0, right = 0, up = 0, down = 0, finish_row = 0, finish_column = 0, goBack;
    while(correctPosition == 0)
    {

        for (int i = 1; i <= board[row][column].num_pieces; i++)
        {
            printf("%d Step : ", i);
            scanf("%d", &step);


            while (step != 2 && step != 4 && step != 6 && step != 8) {
                printf("Not valid move");
                printf("%d Step : ", i);
                scanf("%d", &step);
            }
            if (step == 2)
                down++;
            if (step == 4)
                left++;
            if (step == 6)
                right++;
            if (step == 8)
                up++;
        }

        finish_row = row - up + down;
        finish_column = column - left + right;

        if(board[finish_row][finish_column].type == INVALID || finish_row < 0 || finish_row > 7 || finish_column < 0 || finish_column > 7)
        {
            printf("Moved to an invalid square. Try again\n");
            down = 0;
            up = 0;
            right = 0;
            left = 0;
        }
        else
            correctPosition++;
    }

    move_stack(&board[row][column], &board[finish_row][finish_column], players);
    print_board(board);
}

void position_captured_piece(player *players, square board[8][8])
{
    int acceptMove = 0, row = 0, column = 0;
    while(acceptMove == 0)
    {
        printf("Please type the row you would like to move your piece to : ");
        scanf("%d", &row);
        printf("Please type the column you would like to move your piece to : ");
        scanf("%d", &column);

        if(board[row][column].type == VALID && column > 0 && column < 8 && row > 0 && row < 8)
            acceptMove = 1;
        else
            printf("Invalid move, Try Again!\n");
    }

    move_captured_piece(players, &board[row][column]);
    print_board(board);
}

void move_stack(square *from, square *to, player *players) {
    from->bottom->next = to->stack;
    to->stack = from->stack;
    if (to->bottom == NULL)
        to->bottom = from->bottom;
    from->stack = NULL;
    from->bottom = NULL;
    to->num_pieces += from->num_pieces;
    from->num_pieces = 0;

    if (to->num_pieces == 10) {
        to->bottom = to->stack->next->next->next->next;
        if ((to->bottom->next->next->next->next->next->p_color == RED && players->player_color == RED) ||
            (to->bottom->next->next->next->next->next->p_color == GREEN && players->player_color == GREEN)) {
            players->pieces_captured++;
            to->num_pieces--;
        } else {
            players->pieces_destroyed++;
            to->num_pieces--;
        }

        free(to->bottom->next->next->next->next->next);
    }
    if (to->num_pieces == 9) {
        to->bottom = to->stack->next->next->next->next;

        if ((to->bottom->next->next->next->next->p_color == RED && players->player_color == RED) ||
            (to->bottom->next->next->next->next->p_color == GREEN && players->player_color == GREEN)) {
            players->pieces_captured++;
            to->num_pieces--;
            free(to->bottom->next->next->next->next);
        } else {
            players->pieces_destroyed++;
            to->num_pieces--;
            free(to->bottom->next->next->next->next);
        }
    }
    if (to->num_pieces == 8) {
        to->bottom = to->stack->next->next->next->next;

        if ((to->bottom->next->next->next->p_color == RED && players->player_color == RED) ||
            (to->bottom->next->next->next->p_color == GREEN && players->player_color == GREEN)) {
            players->pieces_captured++;
            to->num_pieces--;
            free(to->bottom->next->next->next);
        } else {
            players->pieces_destroyed++;
            to->num_pieces--;
            free(to->bottom->next->next->next);
        }
    }
    if (to->num_pieces == 7) {
        to->bottom = to->stack->next->next->next->next;

        if ((to->bottom->next->next->p_color == RED && players->player_color == RED) ||
        (to->bottom->next->next->p_color == GREEN && players->player_color == GREEN)) {
            players->pieces_captured++;
            to->num_pieces--;
            free(to->bottom->next->next);
        } else {
            players->pieces_destroyed++;
            to->num_pieces--;
            free(to->bottom->next->next);
        }
    }
    if (to->num_pieces == 6) {
        to->bottom = to->stack->next->next->next->next;

        if ((to->bottom->next->p_color == RED && players->player_color == RED) ||
        (to->bottom->next->p_color == GREEN && players->player_color == GREEN)) {
            players->pieces_captured++;
            to->num_pieces--;
            free(to->bottom->next);
        } else {
            players->pieces_destroyed++;
            to->num_pieces--;
            free(to->bottom->next);
        }

    }

}

void move_captured_piece(player *players, square *moveCapturedPiece)
{
    if(moveCapturedPiece->num_pieces == 0) {
        players->pieces_captured--;
        if(players->player_color == RED)
            set_red(moveCapturedPiece);
        else
            set_green(moveCapturedPiece);
    }
    else {
        piece * curr;

        curr = moveCapturedPiece->stack;
        moveCapturedPiece->stack = (piece *) malloc (sizeof(piece));
        players->pieces_captured--;
        moveCapturedPiece->num_pieces++;

        if(players->player_color == RED)
            moveCapturedPiece->stack->p_color = RED;
        else
            moveCapturedPiece->stack->p_color = GREEN;

        moveCapturedPiece->stack->next = curr;

        if (moveCapturedPiece->num_pieces == 6) {

            moveCapturedPiece->bottom = moveCapturedPiece->stack->next->next->next->next;

            if ((moveCapturedPiece->bottom->next->p_color == RED && players->player_color == RED) || (moveCapturedPiece->bottom->next->p_color == GREEN && players->player_color == GREEN)) {
                players->pieces_captured++;
                moveCapturedPiece->num_pieces--;
                free(moveCapturedPiece->bottom->next);
            }
            else {
                players->pieces_destroyed++;
                moveCapturedPiece->num_pieces--;
                free(moveCapturedPiece->bottom->next);
            }

        }

    }
}



