#include <stdio.h>
#include "game_init.h"
#include "input_output.h"
#include "play_game.h"

int main()
{
    player player1; // struct of player1
    player player2; // struct of player2
    square board[8][8]; // size of board

    initialize_players(&player1, &player2); // Initialize Players

    initialize_board(board); // Initialize board
    print_board(board); // print board

    play_game(player1, player2, board); // play game function

}
