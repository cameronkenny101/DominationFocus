cmake_minimum_required(VERSION 3.15)
project(DominationGame C)

set(CMAKE_C_STANDARD 11)

add_executable(DominationGame src/main.c src/structs.h src/game_init.c src/game_init.h src/input_output.c src/input_output.h src/player_movement.c src/player_movement.h src/play_game.h src/play_game.c)