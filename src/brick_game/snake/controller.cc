#include "controller.h"

namespace s21 {
/**
 * @brief Construct a new Controller:: Controller object
 *
 */
Controller::Controller() {}
/**
 * @brief Destroy the Controller:: Controller object
 *
 */
Controller::~Controller() {}
/**
 * @brief вызывет метод модели для поддержания актуального состояния, для
 * отрисовки
 *
 * @return GameInfo_t
 */
GameInfo_t Controller::ClrUpdateCurrentState() {
  return model.updateCurrentState();
}
/**
 * @brief вызывет метод модели для считывания действия пользователя
 *
 * @param input
 */
void Controller::ClrUserInput(int input) { model.UserInput(input); }
/**
 * @brief вызывет метод модели для обработки действия пользователя
 *
 * @param action
 * @param hold
 */
void Controller::ClruserInput(UserAction_t action, bool hold) {
  model.userInput(action, hold);
}
/**
 * @brief вызывет метод модели для движение змейки
 *
 */
void Controller::ClrMovement() { model.Movement(); }
/**
 * @brief вызывет метод модели для получения актуального состояния игры
 *
 * @return true
 * @return false
 */
bool Controller::ClrGetGameStatus() { return model.GetGameStatus(); }
/**
 * @brief вызывет метод модели для получения актуальной скорости игры
 *
 * @return int
 */
int Controller::ClrGetSpeed() { return model.GetSpeed(); }

}  // namespace s21
