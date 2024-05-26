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
    explicit NewtonFrac(QWidget *parent = nullptr);
    QImage image;
    ~NewtonFrac();

private:
    Ui::NewtonFrac *ui;
    void paintEvent(QPaintEvent *event) override;
    void createNewtonFractal();
};

#endif // NEWTONFRAC_H
