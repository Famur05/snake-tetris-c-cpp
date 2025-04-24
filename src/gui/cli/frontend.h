#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/fsm.h"
#include "../../brick_game/tetris/tetris_lib.h"

#ifdef __cplusplus
extern "C" {
#endif
void snake();
void print_field_snake(s21::GameInfo_t& game_info);
void print_additional_information_snake(s21::GameInfo_t& game_info);
#ifdef __cplusplus
}
#endif
void tetris();
void ncurses_parametrs();
void print_field_tetris(GameInfo_t info_for_field);
void print_figure(all_parameters* get_all_parameters);
void print_additional_information_tetris(all_parameters* get_all_parameters);
void print_enter_tetris();
void print_enter_snake();
void print_space();

#endif  // FRONTEND_H
