//
// Created by camek on 28/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "player_movement.h"
#include "input_output.h"
#include "game_init.h"

// Function for moving piece
void move_piece(player *players, square board[8][8])
{
    int cont = 0, row = 0, column = 0, accept, players_color = 0, square_color = 0;
    char line[20];

    if(players->player_color == RED) // if color is red set to 1. This is then compared later
        players_color = 1;
    else
        players_color = 2; // if green set to 2

    while(cont == 0) // enters while loop as cont is set to 0 initially
    {
        printf("Please type the row of the piece you want to move : ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &row);
        printf("Please type the column of the piece you want to move : ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &column);

        if(row > 7 || row < 0 || column > 7 || column < 0) // if choice is not in array square color will be different to player color and will loop again
            square_color = -1;
        else if(board[row][column].num_pieces == 0) // if no pieces on board will loop again
            square_color = 0;
        else if(board[row][column].stack->p_color == RED) // if co-ordinates are red sets to 1
            square_color = 1;
        else
            square_color = 2; // if coordinates are green set to 2

        if(players_color != square_color) // If you select a piece does not belong to you
        {
            printf("You selected a piece that doesnt belong to you. Please select again\n");
            continue; // While loop runs from start again
        }

        printf("You selected the co-ordinates (row : %d , column : %d). Press 1 to continue or any other number to pick new co-ordinates : ", row, column);
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &accept);
        if(accept == 1)
            cont = 1; // breaks out of the while loop when player accepts the move they made
    }

    printf("8 is up, 4 is left, 6 is right, 2 is down\n"); // movement

    int correctPosition = 0, step, left = 0, right = 0, up = 0, down = 0, finish_row = 0, finish_column = 0, i = 1;
    while(correctPosition == 0) {
        for (i = 1; i <= board[row][column].num_pieces; i++) { // Player moves as many steps as the size of the stack
            printf("%d Step : ", i);
            fgets(line, sizeof(line), stdin);
            sscanf(line, "%d", &step);

            while (step != 2 && step != 4 && step != 6 && step != 8) { // If step value not valid asks again until it is valid
                printf("Not a valid move. Please try again\n");
                printf("%d Step : ", i);
                fgets(line, sizeof(line), stdin);
                sscanf(line, "%d", &step);
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

        finish_row = row - up + down; // co-ordinate for row
        finish_column = column - left + right; // co-ordinate for column

        if(board[finish_row][finish_column].type == INVALID || finish_row < 0 || finish_row > 7 || finish_column < 0 || finish_column > 7) {
            printf("Moved to an invalid square. Try again\n");
            down = 0;
            up = 0;
            right = 0;
            left = 0;
        }
        else if(row == finish_row && column == finish_column) {
            printf("Moved to the same square. Not a valid move!\n");
            down = 0;
            up = 0;
            right = 0;
            left = 0;
        }
        else
            correctPosition++; // exit while loop if player chooses a correct position
    }

    move_stack(&board[row][column], &board[finish_row][finish_column], players); // function for moving stack
    print_board(board); // then print board
}

// Function for positioning a captured piece
void position_captured_piece(player *players, square board[8][8]) {
    int acceptMove = 0, row = 0, column = 0;
    char line[20];

    while(acceptMove == 0) {
        printf("Please type the row you would like to move your piece to : ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &row);
        printf("Please type the column you would like to move your piece to : ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &column);

        if(board[row][column].type == VALID && column > -1 && column < 8 && row > -1 && row < 8) // If position is valid exit while loop
            acceptMove = 1;
        else
            printf("Invalid move, Try Again!\n");
    }

    move_captured_piece(players, &board[row][column]); // Moves captured piece
    print_board(board); // Prints board
}

// Function for moving stack
void move_stack(square *from, square *to, player *players) {
    from->bottom->next = to->stack; // Effectively places the from stack onto the to stack
    to->stack = from->stack; // Then stets the top of to to now be the top of from stack
    if (to->bottom == NULL)
        to->bottom = from->bottom;  // Sets the bottom pointer
    from->stack = NULL; // Sets the from stack to be null
    from->bottom = NULL; // Therefore sets the from bottom pointer to be null to be null
    to->num_pieces += from->num_pieces; // Pieces of to are now the pieces of to + the pieces in from
    from->num_pieces = 0; // From pieces set to 0
    if(to->num_pieces > 5) {
        to->bottom = to->stack->next->next->next->next; // Bottom set to the 5th pointer
        cut_stack(to, players); // Cuts the stack if greater than 5 pieces
    }

}

// Function for cutting stack
void cut_stack(square *to, player *players) {
    piece *curr = to->bottom->next; // Curr is set to the 6th pointer in list

    while(curr != NULL) {
        piece *temp = curr; // temp set to curr
        curr = curr->next; // curr is set to the next pointer in list
        if(temp->p_color == players->player_color) // if piece is same as players color
        {
            players->pieces_captured++; // Increment pieces captured
            free(temp); // free temp
        }
        else {
            players->pieces_destroyed++; // Increment pieces destroyed
            free(temp); // free temp
        }
    }

    to->stack->next->next->next->next->next = NULL; // 6th pointer is set to null
    to->num_pieces = 5; // number of pieces set to 5
}

// Function for moving captured piece
void move_captured_piece(player *players, square *moveCapturedPiece) {
    if(moveCapturedPiece->num_pieces == 0) { // If there is no pieces on square
        players->pieces_captured--; // Decrement the number of pieces captured
        if(players->player_color == RED) // if player is red
            set_red(moveCapturedPiece); // set the square to be red
        else
            set_green(moveCapturedPiece); // set the square to be green
    }
    else {
        piece *curr; // Create pointer for stack called curr
        curr = moveCapturedPiece->stack; // curr is set to stack
        moveCapturedPiece->stack = (piece *) malloc (sizeof(piece)); // mallocs stack
        players->pieces_captured--; // Decrement the number of pieces captured
        moveCapturedPiece->num_pieces++; // Number of pieces on square is incremented

        if(players->player_color == RED) // Sets color of top piece
            moveCapturedPiece->stack->p_color = RED;
        else
            moveCapturedPiece->stack->p_color = GREEN;

        moveCapturedPiece->stack->next = curr; // next value is equal to curr

        if (moveCapturedPiece->num_pieces == 6) { // if a piece is put on a stack of 5 the number of pieces on square is six so we cut the stack here

            moveCapturedPiece->bottom = moveCapturedPiece->stack->next->next->next->next; // ste bottom to the fifth pointer in list

            if (moveCapturedPiece->bottom->next->p_color == players->player_color) { // if piece is same as players color
                players->pieces_captured++; // Increment the number of pieces captured
                moveCapturedPiece->num_pieces--; // Number of pieces on square set back to five
                free(moveCapturedPiece->bottom->next); // free the 6th pointer in list
            }
            else {
                players->pieces_destroyed++; // Increment the number of pieces destroyed
                moveCapturedPiece->num_pieces--; // Number of pieces on square set back to five
                free(moveCapturedPiece->bottom->next); // free the 6th pointer in list
            }

        }

    }
}



