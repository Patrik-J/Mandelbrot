#ifndef mandelbrotgenerator_hpp
#define mandelbrotgenerator_hpp

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "mandelbrot.hpp"
#include <string>

// using namespace cv;

class MandelbrotGenerator
{
public:
    MandelbrotGenerator();
    void setParams(double *params);
    void setSize(int width, int height);
    void setPath(char *directory, char *filename);
    void setPath(std::string directory, std::string filename);

    int generate();

private:
    int iters;
    double r, g, b;
    int width, height;
    std::string directory, filename;
    double max_abs;
    double min_x, max_x;
    double min_y, max_y;

    cv::Mat img;
};

#endif