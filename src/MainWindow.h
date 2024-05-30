#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QColorDialog>

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
    void on_colorPickerBuddhabrot_clicked();

    void on_iterationsNewtonSlider_valueChanged(int value);
    void on_buddhabrotIterationsSlider_valueChanged(int value);
    void on_buddhabrotSamplesSlider_valueChanged(int value);
    void on_colorPickerNewton_clicked();

private:
    void generateNewtonFractal(QImage& image, int width, int height, int xOffset, int yOffset,
        int maxIterations, const QColor& color);
    void generateBuddhabrotFractal(QImage& image, int width, int height, int xOffset, int yOffset,
        int maxIterations, int numSamples, const QColor& color);

private:
    Ui::MainWindow* ui;
    QImage image;
    QColor selectedColorBuddhabrot;
    QColor selectedColorNewton;
};
#endif // MAINWINDOW_H
