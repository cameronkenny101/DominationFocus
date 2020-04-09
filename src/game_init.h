//
// Created by camek on 28/03/2020.
//

#ifndef DOMINATIONGAME_GAME_INIT_H
#define DOMINATIONGAME_GAME_INIT_H

#include "structs.h"

void initialize_players(player *player1, player *player2);

void initialize_board(square board[8][8]);
void set_green(square * s);
void set_red(square * s);


#endif //DOMINATIONGAME_GAME_INIT_H
