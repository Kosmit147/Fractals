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
    explicit BuddhabrotFrac(QWidget *parent = nullptr);
    QImage image;
    ~BuddhabrotFrac();

private:
    Ui::BuddhabrotFrac *ui;
    void paintEvent(QPaintEvent *event) override;
    void createBuddhabrotFractal();
};

#endif // BUDDHABROTFRAC_H
