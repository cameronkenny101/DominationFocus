//
// Created by camek on 28/03/2020.
//

#ifndef DOMINATIONGAME_GAME_INIT_H
#define DOMINATIONGAME_GAME_INIT_H

#include "structs.h"

void initialize_players(player *player1, player *player2); // function protoype
void initialize_board(square board[8][8]); // function protoype
void set_green(square * s); // function protoype
void set_red(square * s); // function protoype


#endif //DOMINATIONGAME_GAME_INIT_H
