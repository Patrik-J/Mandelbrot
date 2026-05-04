#ifndef mandelbrot_hpp
#define mandelbrot_hpp

#include <complex>
#include <math.h>

#define MAX_ITER 1000

class MandelbrotSet
{
public:
    MandelbrotSet();
    int testNumber(std::complex<double> &c);
    void setMaxIters(int iters);
    void setMaxVal(double max);

private:
    std::complex<double> c;
    double max;
    int max_iters = MAX_ITER;
};

#endif