#ifndef MYWIDGETSNAKE_H
#define MYWIDGETSNAKE_H

#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <queue>

#include "../../brick_game/snake/controller.h"

constexpr int kCellSize = 30;
constexpr int kWidth = 300;
constexpr int kHeight = 600;

namespace s21 {

class MyWidgetSnake : public QWidget {
  Q_OBJECT
 public:
  explicit MyWidgetSnake(QWidget *parent = nullptr);
  void Drawing();
  void ResetTimer(const int timer_interval);

  int GetLevel();
  int GetHighScore();
  int GetScore();

 protected:
  void timerEvent(QTimerEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private:
  Controller controller_;
  int timer_id_ = 0;
  std::queue<int> action_queue_;
  const size_t max_queue_size_ = 3;

 signals:
  void GameOver();
  void ChangeLevel();
  void ChangeHighScore();
  void ChangeScore();
  void ChangeSpeed();
};

}  // namespace s21

#endif  // MYWIDGETSNAKE_H
