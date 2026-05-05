#include "mandelbrotgenerator.hpp"

MandelbrotGenerator::MandelbrotGenerator() {};

void MandelbrotGenerator::setParams(double *params)
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

void MandelbrotGenerator::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
};

void MandelbrotGenerator::setPath(char *directory, char *filename)
{
    this->directory = std::string(directory);
    this->filename = std::string(filename);
};

void MandelbrotGenerator::setPath(std::string directory, std::string filename)
{
    this->directory = directory;
    this->filename = filename;
};

int MandelbrotGenerator::generate()
{
    this->img = cv::Mat(this->height, this->width, CV_8UC3, cv::Scalar(0, 0, 0));
    // std::cout << this->directory << std::endl;
    // std::cout << "Directory: " << this->directory << std::endl;
    // std::cout << "Directory: " << std::string(this->directory) << std::endl;

    std::string path = this->directory + "\\" + this->filename + ".jpg";
    // std::cout << "Saving to: " << path << std::endl;
    // cv::imwrite(path, this->img);
    // if (!cv::imwrite(path, this->img))
    // {
    //     std::cerr << "Failed to write image" << std::endl;
    // }
    // cv::imwrite(std::string(this->directory) + "\\test.jpg", this->img);
    MandelbrotSet mbs = MandelbrotSet();
    mbs.setMaxIters(this->iters);
    mbs.setMaxVal(this->max_abs);

    std::complex<double> c;
    int iters;
    int r, g, b;
    double real, imag;
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            real = this->min_x + (this->max_x - this->min_x) * i / double(this->width);
            imag = this->min_y + (this->max_y - this->min_y) * j / double(this->height);
            // c =  + this->min_y + (this->max_y - this->min_y) * j / double(this->height);
            c = (real, imag);
            iters = mbs.testNumber(c);

            if (iters == this->iters)
            {
                r = g = b = 0;
            }
            else
            {
                r = static_cast<int>(iters * this->r) % 256;
                g = static_cast<int>(iters * this->g) % 256;
                b = static_cast<int>(iters * this->b) % 256;
            }
            this->img.at<cv::Vec3b>(j, i) = cv::Vec3b(b, g, r);
        }
    }
    cv::imwrite(path, this->img);

    return 0;
};