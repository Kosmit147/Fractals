#pragma once

#include <QColorDialog>
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/// @brief Klasa głównego okna aplikacji.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    /// @brief Slot obsługujący kliknięcie przycisku generującego fraktal Newtona.
    void on_pushNewtonBtn_clicked();

    /// @brief Slot obsługujący kliknięcie przycisku generującego fraktal Buddhabrota.
    void on_pushBuddhaBtn_clicked();

    /// @brief Slot obsługujący kliknięcie przycisku porównującego oba fraktale.
    void on_pushCompareBtn_clicked();

    /// @brief Slot obsługujący zmianę wartości suwaka iteracji fraktala Newtona.
    /// @param value Nowa wartość suwaka.
    void on_iterationsNewtonSlider_valueChanged(int value);

    /// @brief Slot obsługujący zmianę wartości suwaka iteracji fraktala Buddhabrota.
    /// @param value Nowa wartość suwaka.
    void on_buddhabrotIterationsSlider_valueChanged(int value);

    /// @brief Slot obsługujący zmianę wartości próbek dla fraktala Buddhabrota.
    /// @param value Nowa wartość suwaka.
    void on_buddhabrotSamplesSlider_valueChanged(int value);

    /// @brief Slot obsługujący kliknięcie przycisku wyboru koloru dla fraktala Newtona.
    void on_colorPickerNewton_clicked();

    /// @brief Slot obsługujący kliknięcie przycisku wyboru koloru dla fraktala Buddhabrota.
    void on_colorPickerBuddhabrot_clicked();

private:
    /// @brief Generuje fraktal Newtona.
    /// @param image Obraz, na którym rysowany jest fraktal.
    /// @param width Szerokość obrazu.
    /// @param height Wysokość obrazu.
    /// @param xOffset Przesunięcie w osi X.
    /// @param yOffset Przesunięcie w osi Y.
    /// @param maxIterations Maksymalna liczba iteracji.
    /// @param color Kolor używany do rysowania fraktala.
    void generateNewtonFractal(QImage& image, int width, int height, int xOffset, int yOffset,
                               int maxIterations, const QColor& color);

    /// @brief Generuje fraktal Buddhabrota.
    /// @param image Obraz, na którym rysowany jest fraktal.
    /// @param width Szerokość obrazu.
    /// @param height Wysokość obrazu.
    /// @param xOffset Przesunięcie w osi X.
    /// @param yOffset Przesunięcie w osi Y.
    /// @param maxIterations Maksymalna liczba iteracji.
    /// @param numSamples Liczba próbek.
    /// @param color Kolor używany do rysowania fraktala.
    void generateBuddhabrotFractal(QImage& image, int width, int height, int xOffset, int yOffset,
                                   int maxIterations, int numSamples, const QColor& color);

private:
    Ui::MainWindow* ui;
    QImage image;
    QColor selectedColorBuddhabrot;
    QColor selectedColorNewton;
};
