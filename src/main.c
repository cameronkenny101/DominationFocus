#include <stdio.h>
#include "game_init.h"
#include "input_output.h"
#include "player_movement.h"
#include "play_game.h"

int main()
{
    player player1;
    player player2;
    square board[8][8];

    initialize_players(&player1, &player2);

    initialize_board(board);
    print_board(board);

    play_game(player1, player2, board);

}
