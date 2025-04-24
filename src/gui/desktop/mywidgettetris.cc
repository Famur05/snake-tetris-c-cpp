#include "mywidgettetris.h"

namespace s21 {

MyWidgetTetris::MyWidgetTetris(QWidget *parent) : QWidget{parent} {
  setFocusPolicy(Qt::StrongFocus);
  setFixedSize(kWidth, kHeight);
  timer_id_ = startTimer(50);
  start_game();
  get_all_parameters_ = getting_all_parameters();
}

void MyWidgetTetris::Drawing() {
  QPainter qpainter(this);
  if (game_status() == GAME_IS_ON) {
    GameInfo_t info_for_field = updateCurrentState();
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        if (info_for_field.field[i][j] == 1) {
          qpainter.setBrush(Qt::red);
          qpainter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);
        } else {
          qpainter.setBrush(Qt::white);
          qpainter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);
        }
      }
    }
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (get_all_parameters_->figure_parameters.arr[i][j] == 1) {
          int x_field = get_all_parameters_->figure_parameters.x + j;
          int y_field = get_all_parameters_->figure_parameters.y + i;
          qpainter.setBrush(Qt::green);
          qpainter.drawRect(x_field * kCellSize, y_field * kCellSize, kCellSize,
                            kCellSize);
        }
      }
    }
    emit ChangeNextFigure();
  }
}

void MyWidgetTetris::DoGameOver() { end_game(); }

int MyWidgetTetris::GetLevel() {
  return get_all_parameters_->game_parametrs.level;
}

int MyWidgetTetris::GetHighScore() {
  return get_all_parameters_->game_parametrs.high_score;
}

int MyWidgetTetris::GetScore() {
  return get_all_parameters_->game_parametrs.score;
}

int **MyWidgetTetris::GetNextFigure() {
  return get_all_parameters_->game_parametrs.next;
}

void MyWidgetTetris::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  if (game_status() == GAME_IS_ON) {
    if (get_all_parameters_->game_parametrs.pause == 1) {
      if (!action_queue_.empty()) {
        int action = action_queue_.front();
        action_queue_.pop();
        userInput(static_cast<UserAction_t>(action), 1);
      }
      timer_for_fall(get_all_parameters_);
      movement(get_all_parameters_);
      emit ChangeLevel();
      emit ChangeHighScore();
      emit ChangeScore();
      emit ChangeSpeed();
    }
  } else {
    if (timer_id_ != 0) {
      killTimer(timer_id_);
      timer_id_ = 0;
    }
    emit GameOver();
  }
  this->update();
}

void MyWidgetTetris::keyPressEvent(QKeyEvent *event) {
  int input = event->key();
  switch (input) {
    case Qt::Key_Space:
      userInput(Pause, 1);
      break;
    case Qt::Key_Escape:
      userInput(Terminate, 1);
      break;
    case Qt::Key_Left:
      if (action_queue_.size() < max_queue_size_) {
        action_queue_.push(Left);
      }
      break;
    case Qt::Key_Right:
      if (action_queue_.size() < max_queue_size_) {
        action_queue_.push(Right);
      }
      break;
    case Qt::Key_Up:
      if (action_queue_.size() < max_queue_size_) {
        action_queue_.push(Up);
      }
      break;
    case Qt::Key_Down:
      if (action_queue_.size() < max_queue_size_) {
        action_queue_.push(Down);
      }
      break;
    case Qt::Key_W:
      userInput(Action, 1);
      break;
    default:
      break;
  }
}

void MyWidgetTetris::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  Drawing();
}

}  // namespace s21
