#ifndef BACKEND_H
#define BACKEND_H

#define HEIGHT 20
#define WIDTH 10
#define GAME_OVER 0
#define GAME_IS_ON 1
#define KEY_LEFT 0404
#define KEY_RIGHT 0405
#define KEY_DOWN 0402
#define KEY_UP 0403

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tetris_lib.h"

typedef struct {
  int x;
  int y;
  int arr[5][5];
} FigureInfo_t;

typedef struct {
  int time_counter;
  int time_for_fall;
} timer;

typedef struct {
  GameInfo_t game_parametrs;
  FigureInfo_t figure_parameters;
  timer timer_for_fall;
  int fall_status;
  int GAME_STATUS;
  int pattern_num;
  int next_pattern_num;
  int ENTER;
} all_parameters;

#ifdef __cplusplus
extern "C" {
#endif

int game_status();

void create_field(GameInfo_t* result);
void remove_field(GameInfo_t* result);
void create_next_figure(GameInfo_t* result);
void remove_next_figure(GameInfo_t* result);

all_parameters* getting_all_parameters();
void initialize_figure(int figure[5][5], int num);

void figure_right(all_parameters* get_all_parameters);
void figure_left(all_parameters* get_all_parameters);
void figure_up(all_parameters* get_all_parameters);
void figure_down(all_parameters* get_all_parameters);
void figure_fall(all_parameters* get_all_parameters);
void figure_action(all_parameters* get_all_parameters);

void timer_for_fall(all_parameters* get_all_parameters);

int check_attaching(all_parameters* get_all_parameters);
void attaching(all_parameters* get_all_parameters);
void clean_filled_lines(all_parameters* get_all_parameters);
void fall_new_figure(all_parameters* get_all_parameters);
void count_score_highScore_level(int score, all_parameters* get_all_parameters);

#ifdef __cplusplus
}
#endif

#endif  // BACKEND_H
