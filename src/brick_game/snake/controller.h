#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {
/**
 * @brief этот класс отвечает за формирование запросов на изменение модели
 *
 */
class Controller {
 public:
  Controller();
  ~Controller();

  GameInfo_t ClrUpdateCurrentState();
  void ClrUserInput(int input);
  void ClruserInput(UserAction_t action, bool hold);
  void ClrMovement();

  bool ClrGetGameStatus();
  int ClrGetSpeed();

 private:
  Model model;
};

}  // namespace s21
#endif  // CONTROLLER_H
