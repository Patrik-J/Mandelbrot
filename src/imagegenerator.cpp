#include "imagegenerator.hpp"

ImageGenerator::ImageGenerator() {};

void ImageGenerator::setParams(double *params)
{
    this->iters = int(params[0]);
    this->r = params[1];
    this->g = params[2];
    this->g = params[3];
    this->max_abs = params[4];
    this->min_x = params[5];
    this->max_x = params[6];
    this->min_y = params[7];
    this->max_y = params[8];
};

void ImageGenerator::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
};

void ImageGenerator::setPath(char *directory, char *filename)
{
    this->directory = directory;
    this->filename = filename;
};

void ImageGenerator::setPath(std::string directory, std::string filename)
{
    this->directory = directory.c_str();
    this->filename = filename.c_str();
};

int ImageGenerator::generate()
{
    // this->img = cv::Mat(this->width, this->height, CV_8UC3, cv::Scalar(0, 0, 0));
    // cv::imwrite("test.jpg", this->img);
    MandelbrotSet mbs = MandelbrotSet();
    mbs.setMaxIters(this->iters);
    mbs.setMaxVal(this->max_abs);

    std::complex<double> c;
    int iters;
    int r, g, b;

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            c = this->min_x + (this->max_x * i) / double(this->width) + this->min_y + (this->max_y * j) / double(this->height);
            iters = mbs.testNumber(c);
        }
    }

    return 0;
};