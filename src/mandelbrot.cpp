#include "mandelbrot.hpp"

MandelbrotSet::MandelbrotSet(std::complex<double> c) {
    this->c = c;
};

int MandelbrotSet::testNumber(std::complex<double> z) {
    
    std::complex<double> _z = &z;
    int iter = 0;
    while (abs(_z) < this->max && iter < this->max_iters) {
        _z *= _z
        _z += this->c;
        iter++;
    }
    if (iter == 0) iter = 1;

    return iter;
};

void MandelbrotSet::setMaxVal(double max) {
    this->max = max;
};

void MandelbrotSet::setMaxIters(int iters) {
    this->max_iters = iters;
};