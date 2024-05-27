#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <complex>

#include <QColor>
#include <QImage>
#include <QPainter>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), image(800, 600, QImage::Format_RGB32)
{
    ui->setupUi(this);
    ui->iterationsCountlabel->setText(QString::number(ui->iterationsSlider->value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushNewtonBtn_clicked()
{
       generateNewtonFractal(image, ui->iterationsSlider->value());
       QImage fractalImage = getImage();
       ui->labelView->setPixmap(QPixmap::fromImage(fractalImage));
}

void MainWindow::on_pushBuddhaBtn_clicked()
{
    generateBuddhabrotFractal(image,ui->iterationsSlider->value());
    QImage fractalImage = getImage();
    ui->labelView->setPixmap(QPixmap::fromImage(fractalImage));
}

void MainWindow::on_pushCompareBtn_clicked()
{
    generateBuddhabrotFractalToCompare(image);
    generateNewtonFractalToCompare(image);
    QImage fractalImage = getImage();
    ui->labelView->setPixmap(QPixmap::fromImage(fractalImage));
}

QImage MainWindow::getImage() const
{
    return image;
}

void MainWindow::generateNewtonFractal(QImage &image, int maxIterations)
{
    int width = image.width();
    int height = image.height();

    double scale = 3.0;
    double offsetX = -1.5;
    double offsetY = -1.5;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::complex<double> z(scale * (x - width / 2.0) / (width / 2.0) + offsetX,
                scale * (y - height / 2.0) / (height / 2.0) + offsetY);

            int iteration = 0;
            const std::complex<double> roots[] = { std::complex<double>(1, 0),
                std::complex<double>(-0.5, sqrt(3) / 2),
                std::complex<double>(-0.5, -sqrt(3) / 2) };
            const QColor colors[] = { Qt::red, Qt::green, Qt::blue };

            while (iteration < maxIterations) {
                std::complex<double> f = z * z * z - 1.0;
                std::complex<double> f_prime = 3.0 * z * z;
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

void MainWindow::generateBuddhabrotFractal(QImage &image, int maxIterations)
{
    int width = image.width();
    int height = image.height();

    int numSamples = 1000000;

    std::vector<int> histogram(width * height, 0);

    auto scale = [=](double value, double minSrc, double maxSrc, double minDst,
                     double maxDst) {
        return minDst + (value - minSrc) * (maxDst - minDst) / (maxSrc - minSrc);
    };

    for (int i = 0; i < numSamples; ++i) {
        double cr = scale(rand() / (double)RAND_MAX, 0, 1, -2, 2);
        double ci = scale(rand() / (double)RAND_MAX, 0, 1, -2, 2);
        std::complex<double> c(cr, ci);
        std::complex<double> z = c;
        std::vector<std::complex<double>> trajectory;

        int iteration;

        for (iteration = 0; iteration < maxIterations; ++iteration) {
            if (std::norm(z) > 4.0) {
                break;
            }
            z = z * z + c;
            trajectory.push_back(z);
        }

        if (iteration < maxIterations) {
            for (const auto& point : trajectory) {
                int x = scale(point.real(), -2, 2, 0, width);
                int y = scale(point.imag(), -2, 2, 0, height);

                if (x >= 0 && x < width && y >= 0 && y < height) {
                    ++histogram[y * width + x];
                }
            }
        }
    }

    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int count = histogram[y * width + x];
            int colorValue =
                scale(std::log(count + 1), 0, std::log(maxCount + 1), 0, 255);
            image.setPixel(x, y, QColor(colorValue, colorValue, colorValue).rgb());
        }
    }
}

void MainWindow::generateBuddhabrotFractalToCompare(QImage &image)
{
    int width = image.width();
       int height = image.height();
       int halfHeight = height / 2;

       int maxIterations = 1000;
       int numSamples = 1000000;

       std::vector<int> histogram(width * halfHeight, 0);

       auto scale = [=](double value, double minSrc, double maxSrc, double minDst,
                        double maxDst) {
           return minDst + (value - minSrc) * (maxDst - minDst) / (maxSrc - minSrc);
       };

       for (int i = 0; i < numSamples; ++i) {
           double cr = scale(rand() / (double)RAND_MAX, 0, 1, -2, 2);
           double ci = scale(rand() / (double)RAND_MAX, 0, 1, -2, 2);
           std::complex<double> c(cr, ci);
           std::complex<double> z = c;
           std::vector<std::complex<double>> trajectory;

           int iteration;

           for (iteration = 0; iteration < maxIterations; ++iteration) {
               if (std::norm(z) > 4.0) {
                   break;
               }
               z = z * z + c;
               trajectory.push_back(z);
           }

           if (iteration < maxIterations) {
               for (const auto& point : trajectory) {
                   int x = scale(point.real(), -2, 2, 0, width);
                   int y = scale(point.imag(), -2, 2, 0, halfHeight);

                   if (x >= 0 && x < width && y >= 0 && y < halfHeight) {
                       ++histogram[y * width + x];
                   }
               }
           }
       }

       int maxCount = *std::max_element(histogram.begin(), histogram.end());

       for (int y = 0; y < halfHeight; ++y) {
           for (int x = 0; x < width; ++x) {
               int count = histogram[y * width + x];
               int colorValue =
                   scale(std::log(count + 1), 0, std::log(maxCount + 1), 0, 255);
               image.setPixel(x, y + halfHeight, QColor(colorValue, colorValue, colorValue).rgb());
           }
       }
}

void MainWindow::generateNewtonFractalToCompare(QImage &image)
{
    int width = image.width();
    int height = image.height() / 2;

    double scale = 3.0;
    double offsetX = -1.5;
    double offsetY = -1.5;

    int maxIterations = 50;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::complex<double> z(scale * (x - width / 2.0) / (width / 2.0) + offsetX,
                scale * (y - height / 2.0) / (height / 2.0) + offsetY);

            int iteration = 0;
            const std::complex<double> roots[] = { std::complex<double>(1, 0),
                std::complex<double>(-0.5, sqrt(3) / 2),
                std::complex<double>(-0.5, -sqrt(3) / 2) };
            const QColor colors[] = { Qt::red, Qt::green, Qt::blue };

            while (iteration < maxIterations) {
                std::complex<double> f = z * z * z - 1.0;
                std::complex<double> f_prime = 3.0 * z * z;
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

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{


}

void MainWindow::on_iterationsSlider_valueChanged(int value)
{
    ui->iterationsCountlabel->setText(QString::number(value));
    //generateNewtonFractal(image, value);
    //QImage fractalImage = getImage();
    //ui->labelView->setPixmap(QPixmap::fromImage(fractalImage));
}
