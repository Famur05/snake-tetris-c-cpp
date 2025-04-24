#include "mywidgetsnake.h"

namespace s21 {

MyWidgetSnake::MyWidgetSnake(QWidget *parent) : QWidget{parent} {
  setFocusPolicy(Qt::StrongFocus);
  setFixedSize(kWidth, kHeight);
  timer_id_ = startTimer(controller_.ClrGetSpeed());
}

void MyWidgetSnake::Drawing() {
  GameInfo_t game_info = controller_.ClrUpdateCurrentState();

  QPainter qpainter(this);
  if (controller_.ClrGetGameStatus() == GAME_IS_ON) {
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        if (game_info.field[i][j] == 1) {
          qpainter.setBrush(Qt::green);
          qpainter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);
        } else if (game_info.field[i][j] == 2) {
          qpainter.setBrush(Qt::red);
          qpainter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);
        } else {
          qpainter.setBrush(Qt::white);
          qpainter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);
        }
      }
    }
  }
}

void MyWidgetSnake::ResetTimer(const int timer_interval) {
  if (timer_id_ != 0) {
    killTimer(timer_id_);
  }
  timer_id_ = startTimer(timer_interval);
}

int MyWidgetSnake::GetLevel() {
  return (controller_.ClrUpdateCurrentState().level);
}

int MyWidgetSnake::GetHighScore() {
  return controller_.ClrUpdateCurrentState().high_score;
}

int MyWidgetSnake::GetScore() {
  return controller_.ClrUpdateCurrentState().score;
}

void MyWidgetSnake::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  if (controller_.ClrGetGameStatus() == GAME_IS_ON) {
    if (controller_.ClrUpdateCurrentState().pause == 1) {
      if (!action_queue_.empty()) {
        int action = action_queue_.front();
        action_queue_.pop();
        controller_.ClruserInput(static_cast<UserAction_t>(action), 1);
      }
      controller_.ClrMovement();
      emit ChangeLevel();
      emit ChangeHighScore();
      emit ChangeScore();
      emit ChangeSpeed();
    }
    ResetTimer(controller_.ClrGetSpeed());
  } else {
    if (timer_id_ != 0) {
      killTimer(timer_id_);
      timer_id_ = 0;
    }
    emit GameOver();
  }
  this->update();
}

void MyWidgetSnake::keyPressEvent(QKeyEvent *event) {
  int input = event->key();
  switch (input) {
    case Qt::Key_Space:
      controller_.ClruserInput(Pause, 1);
      break;
    case Qt::Key_Escape:
      controller_.ClruserInput(Terminate, 1);
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
      controller_.ClruserInput(Action, 1);
      break;
    default:
      break;
  }
}

void MyWidgetSnake::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  Drawing();
}

}  // namespace s21
