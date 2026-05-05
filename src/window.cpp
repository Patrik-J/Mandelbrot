#include "window.hpp"

#include "filedialog.hpp"

Window::Window(int width, int height, int fps, const char *title)
{
    this->width = width;
    this->height = height;
    this->fps = fps;
    this->title = title;
    this->screen_index = HOME_PAGE;
    this->conversion_error_dialog = false;
    this->create_mandelbrot = false;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, title);
    SetWindowMinSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    SetExitKey(KEY_NULL);
    SetTargetFPS(fps);
    while (!WindowShouldClose())
    {
        if (this->create_mandelbrot)
        {
            this->create_mandelbrot = false;
            MandelbrotGenerator ig = MandelbrotGenerator();
            ig.setParams(this->params + 2);
            ig.setSize(this->params[0], this->params[1]);
            std::vector<std::string> path = AskForDirectoryFilename();
            if (!path.empty())
            {
                ig.setPath(path[0], path[1]);
                ig.generate();
                this->last_img = LoadTexture(DirectoryFilenameToPNGPath(path[0], path[1]).c_str());
                this->screen_index = IMAGE_PAGE;
            }
        };
        BeginDrawing();
        switch (this->screen_index)
        {
        case HOME_PAGE:
            this->HomeScreen();
            break;
        case SETTINGS_PAGE:
            this->SettingsScreen();
            break;
        case IMAGE_PAGE:
            this->ImageScreen();
            break;
        }
        EndDrawing();
    }
    this->HomeScreen();
    CloseWindow();
};

void Window::HomeScreen()
{
    ClearBackground(WHITE);
    this->checkForResize();

    this->printCenteredText("Mandelbrot Set Generator", 40, 0, -int(0.1 * this->height), BLACK);
    this->printCenteredBlinkingText("Click or press 'Enter'/'Space' to start. :D", 30, 25, 0.8, 0, int(0.1 * this->height), RED);

    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        this->screen_index = SETTINGS_PAGE;
    }
};

void Window::SettingsScreen()
{
    ClearBackground(BLACK);
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->screen_index = HOME_PAGE;
    }

    this->checkForResize();
    this->printCenteredText("Generator Parameters", 40, 0, -int(0.4 * this->height), SKYBLUE);

    // max iterations
    TextLabel iterLabel = TextLabel("Max number of iterations: ");
    iterLabel.setFont(30);
    iterLabel.setPosition(int(0.3 * this->width), int(0.2 * this->height));
    iterLabel.setTextColor(WHITE);
    iterLabel.draw();

    static TextField iterField = TextField(150, 40);
    iterField.setCharLimit(10);
    iterField.setFont(30);
    iterField.setColor(BLACK, WHITE, BLACK, VIOLET);
    iterField.setBorderWidth(3);
    iterField.setPosition(int(0.7 * this->width), int(0.2 * this->height));
    iterField.blinkCursor();
    iterField.draw();

    // iterations to red
    TextLabel redLabel = TextLabel("Red: ");
    redLabel.setFont(30);
    redLabel.setPosition(int(0.3 * this->width), int(0.25 * this->height));
    redLabel.setTextColor(RED);
    redLabel.draw();

    static TextField redField = TextField(150, 40);
    redField.setCharLimit(10);
    redField.setFont(30);
    redField.setColor(BLACK, WHITE, BLACK, RED);
    redField.setBorderWidth(3);
    redField.setPosition(int(0.7 * this->width), int(0.25 * this->height));
    redField.blinkCursor();
    redField.setNumberField();
    redField.draw();

    // iterations to green
    TextLabel greenLabel = TextLabel("Green: ");
    greenLabel.setFont(30);
    greenLabel.setPosition(int(0.3 * this->width), int(0.3 * this->height));
    greenLabel.setTextColor(GREEN);
    greenLabel.draw();

    static TextField greenField = TextField(150, 40);
    greenField.setCharLimit(10);
    greenField.setFont(30);
    greenField.setColor(BLACK, WHITE, BLACK, GREEN);
    greenField.setBorderWidth(3);
    greenField.setPosition(int(0.7 * this->width), int(0.3 * this->height));
    greenField.blinkCursor();
    greenField.draw();

    // iterations to blue
    TextLabel blueLabel = TextLabel("Blue: ");
    blueLabel.setFont(30);
    blueLabel.setPosition(int(0.3 * this->width), int(0.35 * this->height));
    blueLabel.setTextColor(BLUE);
    blueLabel.draw();

    static TextField blueField = TextField(150, 40);
    blueField.setCharLimit(10);
    blueField.setFont(30);
    blueField.setColor(BLACK, WHITE, BLACK, BLUE);
    blueField.setBorderWidth(3);
    blueField.setPosition(int(0.7 * this->width), int(0.35 * this->height));
    blueField.blinkCursor();
    blueField.draw();

    // max absolute value
    TextLabel maxLabel = TextLabel("Max abs: ");
    maxLabel.setFont(30);
    maxLabel.setPosition(int(0.3 * this->width), int(0.4 * this->height));
    maxLabel.setTextColor(WHITE);
    maxLabel.draw();

    static TextField maxField = TextField(150, 40);
    maxField.setCharLimit(10);
    maxField.setFont(30);
    maxField.setColor(BLACK, WHITE, BLACK, VIOLET);
    maxField.setBorderWidth(3);
    maxField.setPosition(int(0.7 * this->width), int(0.4 * this->height));
    maxField.blinkCursor();
    maxField.draw();

    // x min
    TextLabel xminLabel = TextLabel("x Min ");
    xminLabel.setFont(30);
    xminLabel.setPosition(int(0.3 * this->width), int(0.45 * this->height));
    xminLabel.setTextColor(WHITE);
    xminLabel.draw();

    static TextField xminField = TextField(150, 40);
    xminField.setCharLimit(10);
    xminField.setFont(30);
    xminField.setColor(BLACK, WHITE, BLACK, VIOLET);
    xminField.setBorderWidth(3);
    xminField.setPosition(int(0.7 * this->width), int(0.45 * this->height));
    xminField.blinkCursor();
    xminField.draw();

    // x max
    TextLabel xmaxLabel = TextLabel("x Max: ");
    xmaxLabel.setFont(30);
    xmaxLabel.setPosition(int(0.3 * this->width), int(0.5 * this->height));
    xmaxLabel.setTextColor(WHITE);
    xmaxLabel.draw();

    static TextField xmaxField = TextField(150, 40);
    xmaxField.setCharLimit(10);
    xmaxField.setFont(30);
    xmaxField.setColor(BLACK, WHITE, BLACK, VIOLET);
    xmaxField.setBorderWidth(3);
    xmaxField.setPosition(int(0.7 * this->width), int(0.5 * this->height));
    xmaxField.blinkCursor();
    xmaxField.draw();

    // y min
    TextLabel yminLabel = TextLabel("y Min ");
    yminLabel.setFont(30);
    yminLabel.setPosition(int(0.3 * this->width), int(0.55 * this->height));
    yminLabel.setTextColor(WHITE);
    yminLabel.draw();

    static TextField yminField = TextField(150, 40);
    yminField.setCharLimit(10);
    yminField.setFont(30);
    yminField.setColor(BLACK, WHITE, BLACK, VIOLET);
    yminField.setBorderWidth(3);
    yminField.setPosition(int(0.7 * this->width), int(0.55 * this->height));
    yminField.blinkCursor();
    yminField.draw();

    // y max
    TextLabel ymaxLabel = TextLabel("y Max: ");
    ymaxLabel.setFont(30);
    ymaxLabel.setPosition(int(0.3 * this->width), int(0.6 * this->height));
    ymaxLabel.setTextColor(WHITE);
    ymaxLabel.draw();

    static TextField ymaxField = TextField(150, 40);
    ymaxField.setCharLimit(10);
    ymaxField.setFont(30);
    ymaxField.setColor(BLACK, WHITE, BLACK, VIOLET);
    ymaxField.setBorderWidth(3);
    ymaxField.setPosition(int(0.7 * this->width), int(0.6 * this->height));
    ymaxField.blinkCursor();
    ymaxField.draw();

    // width
    TextLabel widthLabel = TextLabel("Image Width: ");
    widthLabel.setFont(30);
    widthLabel.setPosition(int(0.3 * this->width), int(0.65 * this->height));
    widthLabel.setTextColor(WHITE);
    widthLabel.draw();

    static TextField widthField = TextField(150, 40);
    widthField.setCharLimit(10);
    widthField.setFont(30);
    widthField.setColor(BLACK, WHITE, BLACK, VIOLET);
    widthField.setBorderWidth(3);
    widthField.setPosition(int(0.7 * this->width), int(0.65 * this->height));
    widthField.blinkCursor();
    widthField.draw();

    // height
    TextLabel heightLabel = TextLabel("Image Height: ");
    heightLabel.setFont(30);
    heightLabel.setPosition(int(0.3 * this->width), int(0.7 * this->height));
    heightLabel.setTextColor(WHITE);
    heightLabel.draw();

    static TextField heightField = TextField(150, 40);
    heightField.setCharLimit(10);
    heightField.setFont(30);
    heightField.setColor(BLACK, WHITE, BLACK, VIOLET);
    heightField.setBorderWidth(3);
    heightField.setPosition(int(0.7 * this->width), int(0.7 * this->height));
    heightField.blinkCursor();
    heightField.draw();

    // start button
    TextButton start = TextButton(200, 100);
    start.setText("Go!");
    start.setTextColor(WHITE);
    start.setBackgroundColor(SKYBLUE);
    start.makeHoverable(PINK, BLACK);
    start.setFont(30);
    start.setPosition(0.5 * this->width, 0.9 * this->height);
    start.setAction([&]()
                    { 
                    char* fields[] = {
                        widthField.getText(),
                        heightField.getText(),
                        iterField.getText(),
                        redField.getText(),
                        greenField.getText(),
                        blueField.getText(),
                        maxField.getText(),
                        xminField.getText(),
                        xmaxField.getText(),
                        yminField.getText(),
                        ymaxField.getText()
                    };
                    std::vector<double> params = getParams(*this, fields, 11);
                    for (int i = 0; i < 11; i++) {
                        this->params[i] = params[i];
                    } 
                    this->create_mandelbrot = true; });
    start.draw();

    if (this->conversion_error_dialog)
    {
        Rectangle rec{
            this->width / 2 - DEFAULT_POP_UP_WIDTH / 2,
            this->height / 2 - DEFAULT_POP_UP_HEIGHT / 2,
            DEFAULT_POP_UP_WIDTH,
            DEFAULT_POP_UP_HEIGHT};
        if (PopUpWindow(rec, "Error in converting char array to double!", "Conversion Error", ERROR) == 1)
        {
            this->conversion_error_dialog = false;
        }
    }
};

void Window::ImageScreen()
{
    ClearBackground(BLACK);
    this->checkForResize();
    if (IsKeyPressed(KEY_ESCAPE))
    {
        this->screen_index = SETTINGS_PAGE;
    }
    DrawTexture(this->last_img, 0, 0, WHITE);
};

void Window::printCenteredText(const char *text, int fontSize, int xOffset, int yOffset, Font font, float spacing, Color tint)
{
    Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);
    Vector2 textPosition = {
        (this->width - textSize.x) / 2.0f + xOffset,
        (this->height - textSize.y) / 2.0f + yOffset};
    DrawTextEx(font, text, textPosition, fontSize, spacing, tint);
};

void Window::printCenteredText(const char *text, int fontSize, int xOffset, int yOffset, Color tint)
{
    Font font = GetFontDefault();
    float spacing = 2.0f;
    this->printCenteredText(text, fontSize, xOffset, yOffset, font, spacing, tint);
};

void Window::printCenteredBlinkingText(const char *text, int maxFontSize, int minFontSize, float period, int xOffset, int yOffset, Color tint)
{
    const float frequency = 2 * PI / period;
    float sine = sinf(frequency * GetTime()) + 1.0f;
    sine *= 0.5f;
    int currentFontSize = maxFontSize - (maxFontSize - minFontSize) * sine;
    this->printCenteredText(text, currentFontSize, xOffset, yOffset, tint);
};

void Window::checkForResize()
{
    if (IsWindowResized())
    {
        this->width = GetScreenWidth();
        this->height = GetScreenHeight();
    }
};

int Window::getHeight()
{
    return this->height;
};

int Window::getWidth()
{
    return this->width;
};

void Window::setConversionError()
{
    this->conversion_error_dialog = true;
};

std::vector<double> getParams(Window window, char **textFields, int params)
{
    try
    {
        std::vector<double> p;

        for (int i = 0; i < params; i++)
        {
            p.push_back(stringToDouble(textFields[i]));
        };
        return p;
    }
    catch (...)
    {
        window.setConversionError();
        return {};
    }
};

std::string DirectoryFilenameToPNGPath(std::string directory, std::string filename)
{
    std::string path = directory + "/" + filename + ".png";
    return path;
};