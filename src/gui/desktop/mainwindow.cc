#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Choose a game");
  this->move(100, 100);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_2_clicked() {
  hide();
  sw = new SnakeWindow(this);
  sw->show();
  sw->setAttribute(Qt::WA_DeleteOnClose, true);
  sw = nullptr;
}

void MainWindow::on_pushButton_clicked() {
  hide();
  tw = new TetrisWindow(this);
  tw->show();
  tw->setAttribute(Qt::WA_DeleteOnClose, true);
  tw = nullptr;
}
