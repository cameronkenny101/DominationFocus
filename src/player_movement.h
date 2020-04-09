//
// Created by camek on 28/03/2020.
//

#ifndef DOMINATIONGAME_PLAYER_MOVEMENT_H
#define DOMINATIONGAME_PLAYER_MOVEMENT_H

#include "structs.h"

void move_piece(player *players, square board[8][8]);
void move_stack(square *from, square *to, player *players);
void move_captured_piece(player *players, square *moveCapturedPiece);
void position_captured_piece(player *players, square board[8][8]);



#endif //DOMINATIONGAME_PLAYER_MOVEMENT_H
