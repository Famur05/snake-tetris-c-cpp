#include "fsm.h"

void start_game() {
  all_parameters* get_all_parameters = getting_all_parameters();
  // выделение памяти для поля и фигуры
  create_field(&get_all_parameters->game_parametrs);
  create_next_figure(&get_all_parameters->game_parametrs);
  // инициализация
  get_all_parameters->GAME_STATUS = GAME_IS_ON;
  get_all_parameters->game_parametrs.pause = 1;
  get_all_parameters->ENTER = 0;
  get_all_parameters->game_parametrs.level = 1;
  get_all_parameters->game_parametrs.speed = 1;
  get_all_parameters->timer_for_fall.time_for_fall = 10;
  // инициализация и работа с фигурами
  get_all_parameters->pattern_num = (rand() % 7) + 1;
  initialize_figure(get_all_parameters->figure_parameters.arr,
                    get_all_parameters->pattern_num);
  get_all_parameters->figure_parameters.x = 3;
  if (get_all_parameters->pattern_num == 1)
    get_all_parameters->figure_parameters.y = -2;
  else {
    get_all_parameters->figure_parameters.y = -1;
  }
  int next[5][5] = {0};
  get_all_parameters->next_pattern_num = (rand() % 7) + 1;
  initialize_figure(next, get_all_parameters->next_pattern_num);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      get_all_parameters->game_parametrs.next[i][j] = next[i][j];
    }
  }
  // принятие макс счета
  FILE* pF = fopen("high_score_tetris.txt", "r");
  if (pF != NULL) {
    fscanf(pF, "%d", &get_all_parameters->game_parametrs.high_score);
    fclose(pF);
  }
}

void user_input_1(int input) {
  switch (input) {
    case '\n':  // Enter
      userInput(Start, 1);
      break;
    case 32:  // Space
      userInput(Pause, 1);
      break;
    case 27:  // Esc
      userInput(Terminate, 1);
      break;
    default:
      break;
  }
}

void user_input_2(int input) {
  switch (input) {
    case KEY_LEFT:
      userInput(Left, 1);
      break;
    case KEY_RIGHT:
      userInput(Right, 1);
      break;
    case KEY_UP:
      userInput(Up, 1);
      break;
    case KEY_DOWN:
      userInput(Down, 1);
      break;
    case 'w':  // поворот
      userInput(Action, 1);
      break;
    case '/':
      userInput(Teleport, 1);
      break;
    default:
      break;
  }
}

void movement(all_parameters* get_all_parameters) {
  if (get_all_parameters->fall_status) {
    figure_down(get_all_parameters);
  }
  if (check_attaching(get_all_parameters)) {
    figure_up(get_all_parameters);
    attaching(get_all_parameters);
    clean_filled_lines(get_all_parameters);
    fall_new_figure(get_all_parameters);
  }
}

void end_game() {
  all_parameters* get_all_parameters = getting_all_parameters();
  // очищение памяти выделенную для поля и фигуры
  remove_field(&get_all_parameters->game_parametrs);
  remove_next_figure(&get_all_parameters->game_parametrs);
  // вывод макс счета
  FILE* pF = fopen("high_score_tetris.txt", "w");
  if (pF != NULL) {
    fprintf(pF, "%d", get_all_parameters->game_parametrs.high_score);
    fclose(pF);
  }
  get_all_parameters->ENTER = 0;
  get_all_parameters->game_parametrs.score = 0;
  get_all_parameters->GAME_STATUS = GAME_OVER;
}