#include "backend.h"

void create_field(GameInfo_t* result) {
  int flag = 0;
  result->field = (int**)calloc(HEIGHT, sizeof(int*));
  if (result->field != NULL) {
    for (int i = 0; i < HEIGHT && !flag; i++) {
      result->field[i] = (int*)calloc(WIDTH, sizeof(int));
      if (result->field[i] == NULL) {
        flag = 1;
      }
    }
  }
}

void remove_field(GameInfo_t* result) {
  if (result->field != NULL) {
    for (int i = 0; i < HEIGHT; i++) {
      if (result->field[i] != NULL) {
        free(result->field[i]);
      }
    }
    free(result->field);
  }
}

void create_next_figure(GameInfo_t* result) {
  int flag = 0;
  result->next = (int**)calloc(5, sizeof(int*));
  if (result->next != NULL) {
    for (int i = 0; i < 5 && !flag; i++) {
      result->next[i] = (int*)calloc(5, sizeof(int));
      if (result->next[i] == NULL) {
        flag = 1;
      }
    }
  }
}

void remove_next_figure(GameInfo_t* result) {
  if (result->next != NULL) {
    for (int i = 0; i < 5; i++) {
      if (result->next[i] != NULL) {
        free(result->next[i]);
      }
    }
    free(result->next);
  }
}

int game_status() {
  all_parameters* get_all_parameters = getting_all_parameters();
  return get_all_parameters->GAME_STATUS;
}

all_parameters* getting_all_parameters() {
  static all_parameters save_all_parameters = {};
  return &save_all_parameters;
}

void initialize_figure(int figure[5][5], int num) {
  int arr[5][5] = {0};
  if (num == 1) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {1, 1, 1, 1, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  } else if (num == 2) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 1, 0, 0, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  } else if (num == 3) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 0, 1, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  } else if (num == 4) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 1, 1, 0, 0},
                         {0, 1, 1, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  } else if (num == 5) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 1, 1, 0},
                         {0, 1, 1, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  } else if (num == 6) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 1, 0, 0},
                         {0, 1, 1, 1, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  } else if (num == 7) {
    int pattern[5][5] = {{0, 0, 0, 0, 0},
                         {0, 1, 1, 0, 0},
                         {0, 0, 1, 1, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
    memcpy(arr, pattern, sizeof(pattern));
  }
  memcpy(figure, arr, sizeof(arr));
}

void figure_right(all_parameters* get_all_parameters) {
  get_all_parameters->figure_parameters.x++;
  if (check_attaching(get_all_parameters)) {
    figure_left(get_all_parameters);
  }
}

void figure_left(all_parameters* get_all_parameters) {
  get_all_parameters->figure_parameters.x--;
  if (check_attaching(get_all_parameters)) {
    figure_right(get_all_parameters);
  }
}

void figure_up(all_parameters* get_all_parameters) {
  get_all_parameters->figure_parameters.y--;
}

void figure_down(all_parameters* get_all_parameters) {
  get_all_parameters->figure_parameters.y++;
  if (check_attaching(get_all_parameters)) {
    figure_up(get_all_parameters);
  }
}

void figure_fall(all_parameters* get_all_parameters) {
  while (!check_attaching(get_all_parameters)) {
    get_all_parameters->figure_parameters.y++;
  }
  figure_up(get_all_parameters);
}

void figure_action(all_parameters* get_all_parameters) {
  if (get_all_parameters->pattern_num != 4) {
    FigureInfo_t* pFigure = &get_all_parameters->figure_parameters;
    int arr[5][5] = {0};
    int past_figure[5][5];
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        arr[i][j] = pFigure->arr[j][4 - i];
      }
    }
    memcpy(past_figure, pFigure->arr, sizeof(pFigure->arr));
    memcpy(pFigure->arr, arr, sizeof(arr));
    if (check_attaching(get_all_parameters)) {
      memcpy(pFigure->arr, past_figure, sizeof(past_figure));
    }
  }
}

void timer_for_fall(all_parameters* get_all_parameters) {
  get_all_parameters->timer_for_fall.time_counter++;
  if (get_all_parameters->timer_for_fall.time_counter >=
      get_all_parameters->timer_for_fall.time_for_fall) {
    get_all_parameters->figure_parameters.y++;
    get_all_parameters->timer_for_fall.time_counter = 0;
  }
}

int check_attaching(all_parameters* get_all_parameters) {
  int flag = 0;
  FigureInfo_t* figure_parameters = &get_all_parameters->figure_parameters;
  int** pField = get_all_parameters->game_parametrs.field;
  for (int i = 0; i < 5 && !flag; i++) {
    for (int j = 0; j < 5 && !flag; j++) {
      if (figure_parameters->arr[i][j] == 1) {
        int x_field = figure_parameters->x + j;
        int y_field = figure_parameters->y + i;
        if (y_field < 0 || y_field >= HEIGHT || x_field < 0 ||
            x_field >= WIDTH) {
          flag = 1;
        } else if (pField[y_field][x_field] == 1) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

void attaching(all_parameters* get_all_parameters) {
  FigureInfo_t* figure_parameters = &get_all_parameters->figure_parameters;
  int** pField = get_all_parameters->game_parametrs.field;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (figure_parameters->arr[i][j] == 1) {
        int x_field = figure_parameters->x + j;
        int y_field = figure_parameters->y + i;
        pField[y_field][x_field] = figure_parameters->arr[i][j];
      }
    }
  }
}

void fall_new_figure(all_parameters* get_all_parameters) {
  get_all_parameters->fall_status = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      get_all_parameters->figure_parameters.arr[i][j] =
          get_all_parameters->game_parametrs.next[i][j];
    }
  }
  get_all_parameters->pattern_num = get_all_parameters->next_pattern_num;
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
  // если после появление новой фигуры будет столкновение, то игра закончится
  if (check_attaching(get_all_parameters)) {
    get_all_parameters->GAME_STATUS = GAME_OVER;
  }
}

void clean_filled_lines(all_parameters* get_all_parameters) {
  int score = 0;
  int** pField = get_all_parameters->game_parametrs.field;
  for (int i = HEIGHT - 1; i >= 0; i--) {
    int flag = 1;
    for (int j = 0; j < WIDTH; j++) {
      if (pField[i][j] == 0) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      score += 1;
      for (int n = i; n > 0; n--) {
        for (int m = 0; m < WIDTH; m++) {
          pField[n][m] = pField[n - 1][m];
        }
      }
      for (int m = 0; m < WIDTH; m++) {
        pField[0][m] = 0;
      }
      i++;
    }
  }
  count_score_highScore_level(score, get_all_parameters);
}

void count_score_highScore_level(int score,
                                 all_parameters* get_all_parameters) {
  switch (score) {
    case 1:
      get_all_parameters->game_parametrs.score += 100;
      break;
    case 2:
      get_all_parameters->game_parametrs.score += 300;
      break;
    case 3:
      get_all_parameters->game_parametrs.score += 700;
      break;
    case 4:
      get_all_parameters->game_parametrs.score += 1500;
      break;
    default:
      break;
  }
  if (get_all_parameters->game_parametrs.score >
      get_all_parameters->game_parametrs.high_score)
    get_all_parameters->game_parametrs.high_score =
        get_all_parameters->game_parametrs.score;
  get_all_parameters->game_parametrs.level =
      (int)get_all_parameters->game_parametrs.score / 600 + 1;
  // увелечение скорости в зависимости от level
  get_all_parameters->timer_for_fall.time_for_fall =
      11 - get_all_parameters->game_parametrs.level;
  get_all_parameters->game_parametrs.speed =
      get_all_parameters->game_parametrs.level;
  if (get_all_parameters->game_parametrs.level == 10)
    get_all_parameters->GAME_STATUS = GAME_OVER;
}