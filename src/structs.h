//
// Created by camek on 27/03/2020.
//

#ifndef DOMINATIONGAME_STRUCTS_H
#define DOMINATIONGAME_STRUCTS_H

typedef enum color {
    RED,
    GREEN
}color;

typedef enum square_type {
    VALID,
    INVALID
}square_type;

typedef struct piece {
    color p_color;
    struct piece * next;
}piece;

typedef struct square {
    square_type type;
    piece * stack;
    piece * bottom;
    int num_pieces;
}square;

typedef struct player {
    color player_color;
    char player_name[30];
    int pieces_captured;
    int pieces_destroyed;
}player;

#endif //DOMINATIONGAME_STRUCTS_H
