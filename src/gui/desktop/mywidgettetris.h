#ifndef MYWIDGETTETRIS_H
#define MYWIDGETTETRIS_H

#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
extern "C" {
#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/fsm.h"
#include "../../brick_game/tetris/tetris_lib.h"
}
#include <queue>

namespace s21 {

constexpr int kCellSize = 30;
constexpr int kWidth = 300;
constexpr int kHeight = 600;

class MyWidgetTetris : public QWidget {
  Q_OBJECT
 public:
  explicit MyWidgetTetris(QWidget* parent = nullptr);
  void Drawing();
  void DoGameOver();

  int GetLevel();
  int GetHighScore();
  int GetScore();
  int** GetNextFigure();

 protected:
  void timerEvent(QTimerEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

 private:
  all_parameters* get_all_parameters_ = nullptr;
  int timer_id_ = 0;
  std::queue<int> action_queue_;
  const size_t max_queue_size_ = 3;

 signals:
  void GameOver();
  void ChangeLevel();
  void ChangeHighScore();
  void ChangeScore();
  void ChangeSpeed();
  void ChangeNextFigure();
};

}  // namespace s21

#endif  // MYWIDGETTETRIS_H
