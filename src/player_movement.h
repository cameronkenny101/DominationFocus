//
// Created by camek on 28/03/2020.
//

#ifndef DOMINATIONGAME_PLAYER_MOVEMENT_H
#define DOMINATIONGAME_PLAYER_MOVEMENT_H

#include "structs.h"

void move_piece(player *players, square board[8][8]); // function prototype
void move_stack(square *from, square *to, player *players); // function prototype
void move_captured_piece(player *players, square *moveCapturedPiece); // function prototype
void position_captured_piece(player *players, square board[8][8]); // function prototype



#endif //DOMINATIONGAME_PLAYER_MOVEMENT_H
