//
// Created by camek on 28/03/2020.
//

#ifndef DOMINATIONGAME_GAME_INIT_H
#define DOMINATIONGAME_GAME_INIT_H

#include "structs.h"

void initialize_players(player *player1, player *player2); // function prototype
void initialize_board(square board[8][8]); // function prototype
void set_green(square * s); // function prototype
void set_red(square * s); // function prototype


#endif //DOMINATIONGAME_GAME_INIT_H
