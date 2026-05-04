#ifndef mandelbrot_hpp
#define mandelbrot_hpp

#include <complex>
#include <math>

#define MAX_ITER 1000

class MandelbrotSet {
    public:
        MandelbrotSet(std::complex<double> c);
        int testNumber(std::complex<double> z);
        void setMaxIters(int iters);
        void setMaxVal(double max);

    private:
        std::complex<double> c;
        double max;
        int max_iters = MAX_ITER;
};

#endif 