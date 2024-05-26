#include "NewtonFrac.h"
#include "ui_NewtonFrac.h"
#include <QImage>
#include <QPainter>
#include <QColor>
#include <complex>

NewtonFrac::NewtonFrac(QWidget *parent) :
    QDialog(parent),
    image(800, 600, QImage::Format_RGB32),
    ui(new Ui::NewtonFrac)
{
    ui->setupUi(this);
    createNewtonFractal();
}

NewtonFrac::~NewtonFrac()
{
    delete ui;
}

void NewtonFrac::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void NewtonFrac::createNewtonFractal()
{
    int width = image.width();
           int height = image.height();
           double scale = 3.0;
           double offsetX = -1.5;
           double offsetY = -1.5;
           int maxIterations = 50;

           for (int y = 0; y < height; ++y) {
               for (int x = 0; x < width; ++x) {
                   std::complex<double> z(
                       scale * (x - width / 2.0) / (width / 2.0) + offsetX,
                       scale * (y - height / 2.0) / (height / 2.0) + offsetY
                   );

                   int iteration = 0;
                   const std::complex<double> roots[] = {
                       std::complex<double>(1, 0),
                       std::complex<double>(-0.5, sqrt(3) / 2),
                       std::complex<double>(-0.5, -sqrt(3) / 2)
                   };
                   const QColor colors[] = {Qt::red, Qt::green, Qt::blue};

                   while (iteration < maxIterations) {
                       std::complex<double> f = z*z*z - 1.0;
                       std::complex<double> f_prime = 3.0*z*z;
                       std::complex<double> z_next = z - f / f_prime;

                       if (std::abs(z_next - z) < 1e-6)
                           break;

                       z = z_next;
                       ++iteration;
                   }

                   QColor color = Qt::black;
                   if (iteration < maxIterations) {
                       double min_distance = std::numeric_limits<double>::max();
                       int root_index = -1;

                       for (int i = 0; i < 3; ++i) {
                           double distance = std::abs(z - roots[i]);
                           if (distance < min_distance) {
                               min_distance = distance;
                               root_index = i;
                           }
                       }

                       if (root_index != -1)
                           color = colors[root_index];
                   }

                   image.setPixel(x, y, color.rgb());
               }
           }
}

