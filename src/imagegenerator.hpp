#ifndef imagegenerator_hpp
#define imagegenerator_hpp

#include "mandelbrot.hpp"
// #include <opencv2/opencv.hpp>

class ImageGenerator
{
public:
    ImageGenerator();
    void setParams(double *params);
    void setSize(int width, int height);
    void setPath(char *directory, char *filename);
    void setPath(std::string directory, std::string filename);

    int generate();

private:
    int iters;
    double r, g, b;
    int width, height;
    const char *directory, *filename;
    double max_abs;
    double min_x, max_x;
    double min_y, max_y;

    // cv::Mat img;
};

#endif