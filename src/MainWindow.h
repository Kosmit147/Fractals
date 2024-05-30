#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

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

    void on_iterationsNewtonSlider_valueChanged(int value);
    void on_buddhabrotIterationsSlider_valueChanged(int value);
    void on_buddhabrotSamplesSlider_valueChanged(int value);

private:
    void generateNewtonFractal(QImage& image, int width, int height, int xOffset, int yOffset,
        int maxIterations);
    void generateBuddhabrotFractal(QImage& image, int width, int height, int xOffset, int yOffset,
        int maxIterations, int numSamples);

private:
    Ui::MainWindow* ui;
    QImage image;
};
#endif // MAINWINDOW_H
