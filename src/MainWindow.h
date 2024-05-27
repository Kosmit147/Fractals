#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void on_pushCompareBtn_clicked();
    QImage getImage() const;
    void generateNewtonFractal(QImage &image, int maxIterations);
    void generateBuddhabrotFractal(QImage &image, int maxIterations);
    void generateBuddhabrotFractalToCompare(QImage &image);
    void generateNewtonFractalToCompare(QImage &image);

    void on_horizontalSlider_sliderMoved(int position);

    void on_iterationsSlider_valueChanged(int value);

private:
    Ui::MainWindow* ui;
    QImage image;
};
#endif // MAINWINDOW_H
