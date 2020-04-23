//
// Created by camek on 06/04/2020.
//

#ifndef DOMINATIONGAME_PLAY_GAME_H
#define DOMINATIONGAME_PLAY_GAME_H

#include "structs.h"


void play_game(player player1, player player2, square board[8][8]); // function prototype
void finish_screen(player winner, int turns, square board[8][8]); // function prototype
void free_memory(square *pieces);

#endif //DOMINATIONGAME_PLAY_GAME_H
