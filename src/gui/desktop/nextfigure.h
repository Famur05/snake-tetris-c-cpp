#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QPainter>
#include <QWidget>

namespace s21 {

constexpr int kCelSize = 30;

class NextFigure : public QWidget {
  Q_OBJECT
 public:
  explicit NextFigure(QWidget *parent = nullptr);
  void Drawing(int **next_figure);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  int figure_[5][5] = {};
};

}  // namespace s21

#endif  // NEXTFIGURE_H
