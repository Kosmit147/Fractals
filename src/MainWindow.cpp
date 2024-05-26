#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushNewtonBtn_clicked()
{
    newtonDialog = new NewtonFrac();
    newtonDialog->show();
    this->hide();
}

void MainWindow::on_pushBuddhaBtn_clicked()
{
    buddhabrotDialog = new BuddhabrotFrac();
    buddhabrotDialog->show();
    this->hide();
}

void MainWindow::on_pushBothBtn_clicked()
{

}
