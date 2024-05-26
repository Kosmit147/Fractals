#include "BuddhabrotFrac.h"
#include "ui_BuddhabrotFrac.h"
#include <QColor>
#include <QImage>
#include <QPainter>
#include <complex>

BuddhabrotFrac::BuddhabrotFrac(QWidget* parent)
    : QDialog(parent), image(800, 600, QImage::Format_RGB32), ui(new Ui::BuddhabrotFrac)
{
    ui->setupUi(this);
    generateBuddhabrotFractal();
}

BuddhabrotFrac::~BuddhabrotFrac()
{
    delete ui;
}

void BuddhabrotFrac::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void BuddhabrotFrac::generateBuddhabrotFractal()
{
    int width = image.width();
    int height = image.height();

    int maxIterations = 1000;
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
