#include "tetris_lib.h"

#include "backend.h"

void userInput(UserAction_t action, bool hold) {
  UNUSED(hold);
  all_parameters* get_all_parameters = getting_all_parameters();
  int val = action;
  switch (val) {
    case Start:
      get_all_parameters->ENTER = 1;
      break;
    case Pause:
      get_all_parameters->game_parametrs.pause *= -1;
      break;
    case Terminate:
      get_all_parameters->GAME_STATUS = GAME_OVER;
      break;
    case Left:
      figure_left(get_all_parameters);
      break;
    case Right:
      figure_right(get_all_parameters);
      break;
    case Up:
      // get_all_parameters->fall_status = 0;
      break;
    case Down:
      get_all_parameters->fall_status = 1;
      break;
    case Action:
      figure_action(get_all_parameters);
      break;
    case 8:
      figure_fall(get_all_parameters);
      break;
    default:
      break;
  }
}

GameInfo_t updateCurrentState() {
  all_parameters* get_all_parameters = getting_all_parameters();
  return get_all_parameters->game_parametrs;
}
