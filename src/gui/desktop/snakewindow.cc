#include "snakewindow.h"

#include <qboxlayout.h>

#include "ui_snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SnakeWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Snake");

  mws = new s21::MyWidgetSnake(ui->widget);
  ui->widget->setLayout(new QVBoxLayout());
  ui->widget->layout()->addWidget(mws);

  connect(mws, &s21::MyWidgetSnake::GameOver, this, &SnakeWindow::CloseGame);
  connect(mws, &s21::MyWidgetSnake::ChangeLevel, this, &SnakeWindow::SetLevel);
  connect(mws, &s21::MyWidgetSnake::ChangeHighScore, this,
          &SnakeWindow::SetHighScore);
  connect(mws, &s21::MyWidgetSnake::ChangeScore, this, &SnakeWindow::SetScore);
  connect(mws, &s21::MyWidgetSnake::ChangeSpeed, this, &SnakeWindow::SetSpeed);
}

SnakeWindow::~SnakeWindow() {
  delete ui;
  delete mws;
}

void SnakeWindow::closeEvent(QCloseEvent *event) {
  if (parent()) {
    QMainWindow *parentWindow = qobject_cast<QMainWindow *>(parent());
    if (parentWindow) {
      parentWindow->show();
    }
  }
  event->accept();
}

void SnakeWindow::SetLevel() {
  ui->label_5->setText(QString::number(mws->GetLevel()));
}

void SnakeWindow::SetHighScore() {
  ui->label_6->setText(QString::number(mws->GetHighScore()));
}

void SnakeWindow::SetScore() {
  ui->label_7->setText(QString::number(mws->GetScore()));
}

void SnakeWindow::SetSpeed() {
  ui->label_8->setText("x" + QString::number(mws->GetLevel()));
}

void SnakeWindow::CloseGame() { this->close(); }
