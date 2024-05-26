#ifndef NEWTONFRAC_H
#define NEWTONFRAC_H

#include <QDialog>
#include <QImage>

namespace Ui {
class NewtonFrac;
}

class NewtonFrac : public QDialog
{
    Q_OBJECT

public:
    explicit NewtonFrac(QWidget* parent = nullptr);
    ~NewtonFrac();

private:
    void paintEvent(QPaintEvent* event) override;
    void generateNewtonFractal();

private:
    Ui::NewtonFrac* ui;
    QImage image;
};

#endif // NEWTONFRAC_H
