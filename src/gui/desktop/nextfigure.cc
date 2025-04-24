#include "nextfigure.h"

namespace s21 {

NextFigure::NextFigure(QWidget *parent) : QWidget{parent} {
  setFixedSize(150, 150);
}

void NextFigure::Drawing(int **next_figure) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      figure_[i][j] = next_figure[i][j];
    }
  }
  update();
}

void NextFigure::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter qpainter(this);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (figure_[i][j] == 1) {
        qpainter.setBrush(Qt::green);
        qpainter.drawRect(j * kCelSize, i * kCelSize, kCelSize, kCelSize);
      }
    }
  }
}

}  // namespace s21
