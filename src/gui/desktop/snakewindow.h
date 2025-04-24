#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QMainWindow>

#include "mywidgetsnake.h"

namespace Ui {
class SnakeWindow;
}

class SnakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit SnakeWindow(QWidget *parent = nullptr);
  ~SnakeWindow();
  void CloseGame();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void SetLevel();
  void SetHighScore();
  void SetScore();
  void SetSpeed();

 private:
  Ui::SnakeWindow *ui;
  s21::MyWidgetSnake *mws;
};

#endif  // SNAKEWINDOW_H
