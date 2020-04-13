//
// Created by camek on 27/03/2020.
//

#ifndef DOMINATIONGAME_STRUCTS_H
#define DOMINATIONGAME_STRUCTS_H

// struct for color type
typedef enum color {
    RED,
    GREEN
}color;

// struct for square type
typedef enum square_type {
    VALID,
    INVALID
}square_type;

// struct for pieces color and pointers to each piece
typedef struct piece {
    color p_color;
    struct piece * next;
}piece;

// struct for square, the number of pieces on a square, pointer to piece top of square and pointer to piece bottom of square
typedef struct square {
    square_type type;
    piece * stack;
    piece * bottom;
    int num_pieces;
}square;

// struct for player, there name, color, pieces captured and pieces destroyed
typedef struct player {
    color player_color;
    char player_name[30];
    int pieces_captured;
    int pieces_destroyed;
}player;

#endif //DOMINATIONGAME_STRUCTS_H
