#include "tetriswindow.h"

#include <qboxlayout.h>

#include <QCloseEvent>

#include "ui_tetriswindow.h"

TetrisWindow::TetrisWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TetrisWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Tetris");

  mwt = new s21::MyWidgetTetris(ui->widget);
  ui->widget->setLayout(new QVBoxLayout());
  ui->widget->layout()->addWidget(mwt);

  nf = new s21::NextFigure(ui->widget_2);
  ui->widget_2->setLayout(new QVBoxLayout());
  ui->widget_2->layout()->addWidget(nf);

  connect(mwt, &s21::MyWidgetTetris::GameOver, this, &TetrisWindow::CloseGame);
  connect(mwt, &s21::MyWidgetTetris::ChangeLevel, this,
          &TetrisWindow::SetLevel);
  connect(mwt, &s21::MyWidgetTetris::ChangeHighScore, this,
          &TetrisWindow::SetHighScore);
  connect(mwt, &s21::MyWidgetTetris::ChangeScore, this,
          &TetrisWindow::SetScore);
  connect(mwt, &s21::MyWidgetTetris::ChangeSpeed, this,
          &TetrisWindow::SetSpeed);
  connect(mwt, &s21::MyWidgetTetris::ChangeNextFigure, this,
          &TetrisWindow::SetNextFigure);
}

TetrisWindow::~TetrisWindow() {
  delete ui;
  delete mwt;
  delete nf;
}

void TetrisWindow::closeEvent(QCloseEvent *event) {
  mwt->DoGameOver();
  if (parent()) {
    QMainWindow *parentWindow = qobject_cast<QMainWindow *>(parent());
    if (parentWindow) {
      parentWindow->show();
    }
  }
  event->accept();
}

void TetrisWindow::SetLevel() {
  ui->label_5->setText(QString::number(mwt->GetLevel()));
}

void TetrisWindow::SetHighScore() {
  ui->label_6->setText(QString::number(mwt->GetHighScore()));
}

void TetrisWindow::SetScore() {
  ui->label_7->setText(QString::number(mwt->GetScore()));
}

void TetrisWindow::SetSpeed() {
  ui->label_8->setText("x" + QString::number(mwt->GetLevel()));
}

void TetrisWindow::SetNextFigure() { nf->Drawing(mwt->GetNextFigure()); }

void TetrisWindow::CloseGame() { this->close(); }
