#ifndef BUDDHABROTFRAC_H
#define BUDDHABROTFRAC_H

#include <QDialog>

namespace Ui {
class BuddhabrotFrac;
}

class BuddhabrotFrac : public QDialog
{
    Q_OBJECT

public:
    explicit BuddhabrotFrac(QWidget* parent = nullptr);
    ~BuddhabrotFrac();

private:
    void paintEvent(QPaintEvent* event) override;
    void generateBuddhabrotFractal();

private:
    Ui::BuddhabrotFrac* ui;
    QImage image;
};

#endif // BUDDHABROTFRAC_H
