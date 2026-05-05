#ifndef window_hpp
#define window_hpp

// #include <raylib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <filesystem>

#include "windowelement.hpp"
#include "mandelbrotgenerator.hpp"
// #include "portable-file-dialogs.h"

inline const int DEFAULT_SCREEN_WIDTH = 1000;
inline const int DEFAULT_SCREEN_HEIGHT = 1000;
inline const char *test = "Mandelbrot Set Generator";

#define HOME_PAGE 1
#define SETTINGS_PAGE 2
#define IMAGE_PAGE 3

class Window
{
public:
    Window(int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGHT, int fps = 60, const char *title = test);

    int getWidth();
    int getHeight();

    void setConversionError();

private:
    int width, height, fps;
    int screen_index;
    const char *title;
    double params[4];
    bool create_mandelbrot = false;
    bool conversion_error_dialog = false;

    void HomeScreen();
    void SettingsScreen();
    void ImageScreen();
    void printCenteredText(const char *text, int fontSize, int xOffset = 0, int yOffset = 0, Font font = GetFontDefault(), float spacing = 2.0, Color tint = BLACK);
    void printCenteredText(const char *text, int fontSize, int xOffset = 0, int yOffset = 0, Color tint = BLACK);
    void printCenteredBlinkingText(const char *text, int maxFontSize, int minFontSize, float period, int xOffset = 0, int yOffset = 0, Color tint = BLACK);
    void checkForResize();
};

std::vector<double> getParams(Window window, char **textFields, int params);

#endif