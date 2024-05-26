#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "BuddhabrotFrac.h"
#include "NewtonFrac.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void on_pushNewtonBtn_clicked();
    void on_pushBuddhaBtn_clicked();
    void on_pushBothBtn_clicked();

  private:
    Ui::MainWindow* ui;
    NewtonFrac* newtonDialog;
    BuddhabrotFrac* buddhabrotDialog;
};
#endif // MAINWINDOW_H
