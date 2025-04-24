#ifndef TETRIS_LIB_H
#define TETRIS_LIB_H

#define UNUSED(x) (void)(x)

#include <stdbool.h>

typedef enum {
  Start,
  Pause,
  Terminate,  // прекратить
  Left,
  Right,
  Up,
  Down,
  Action,  // дейстивие - вращение
  Teleport
} UserAction_t;

typedef struct {
  int **field;     //поле
  int **next;      // следующая фигура
  int score;       // счет
  int high_score;  // рекорд
  int level;       // уровень
  int speed;       // скорость
  int pause;       //пауза
} GameInfo_t;

#ifdef __cplusplus
extern "C" {
#endif

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#ifdef __cplusplus
}
#endif

#endif  // TETRIS_LIB_H