#include "mandelbrot.hpp"

MandelbrotSet::MandelbrotSet() {
};

int MandelbrotSet::testNumber(std::complex<double> &c)
{

    std::complex<double> z_n = 0;
    int iter = 0;

    while (abs(z_n) < this->max && iter < this->max_iters)
    {
        z_n = z_n * z_n + c;
        iter++;
    }
    if (iter == 0)
        iter = 1;

    return iter;
};

void MandelbrotSet::setMaxVal(double max)
{
    this->max = max;
};

void MandelbrotSet::setMaxIters(int iters)
{
    this->max_iters = iters;
};