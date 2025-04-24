#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#include <QMainWindow>

#include "mywidgettetris.h"
#include "nextfigure.h"

namespace Ui {
class TetrisWindow;
}

class TetrisWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit TetrisWindow(QWidget *parent = nullptr);
  ~TetrisWindow();
  void CloseGame();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void SetLevel();
  void SetHighScore();
  void SetScore();
  void SetSpeed();
  void SetNextFigure();

 private:
  Ui::TetrisWindow *ui;
  s21::MyWidgetTetris *mwt;
  s21::NextFigure *nf;
};

#endif  // TETRISWINDOW_H
