#ifndef windowelement_hpp
#define windowelement_hpp

#include <raylib.h>
#include <functional>
#include <cstring>
#include <string>
#include <iostream>

#define MAX_TEXTFIELD_LEN 128
#define STRING_TERMINATE '\0'
#define STRING_NEW_LINE '\n'
#define CURSOR_TIME 0.5

#define DEFAULT_POP_UP_WIDTH 400
#define DEFAULT_POP_UP_HEIGHT 300

class WindowElement
{
public:
    void setFont(int fontSize, Font font = GetFontDefault(), float spacing = 2.0f);
    void setTextColor(Color color);
    void setSize(int width, int height);
    void setPosition(int x, int y);
    virtual void draw() = 0;

protected:
    Font font = GetFontDefault();
    int fontSize = 20;
    float spacing = 2.0;
    int width, height;
    int x, y;
    Color textColor;
};

class TextButton : public WindowElement
{
public:
    TextButton();
    TextButton(int width, int height);

    void setText(const char *text, int fontSize, Color textColor, float spacing = 2.0f, Font font = GetFontDefault());
    void setText(const char *text);
    void setBackgroundColor(Color bgColor);
    void makeHoverable(Color bgHoverColor, Color textHoverColor);
    void unmakeHoverable();
    void setRoundness(bool roundedCorners = false, float roundness = 0.0f, int segments = 0);
    void draw() override;
    void setAction(std::function<void(void)> action);

private:
    const char *text;
    Color bgColor;
    bool hoverable = false;
    Color bgHoverColor, textHoverColor;
    bool highlighted = false;
    Color activeBg, activeText;
    std::function<void(void)> action;

    bool rounded = false;
    float roundness = 0.0f;
    int segments = 0;

    void highlight(bool highlight = true);
    bool mouseOverButton();
    bool mouseClickedOnButton();
};

class TextField : public WindowElement
{
public:
    TextField();
    TextField(int width, int height);
    char *getText();
    void setTextOffset(int x, int y);
    void setCharLimit(int lim = MAX_TEXTFIELD_LEN);
    void setColor(Color textColor = BLACK, Color bgColor = GRAY, Color borderColor = BLACK, Color borderHoverColor = BLACK);
    void draw() override;
    void blinkCursor(bool blink = true, char c = '|');
    void setBorderWidth(int width);
    void setNumberField(bool onlyNumbers = true);

private:
    char *text;
    int last_char = 0;
    int max_len;
    Rectangle textBox;
    int xOffset = 5, yOffset = 8;
    Color bgColor, borderColor, borderHoverColor;
    bool blinking_cursor = false;
    char cursor_char;
    bool show_cursor = false;
    int border_width = 1;
    bool only_numbers = true;

    float time_since_last_frame = 0;

    bool fieldActivated = false;
    void checkActivation();
    void readUserInput();
    void writeUserInput(char c);
    void writeTextToTextField();
    void clearBuffer();
    bool validCharacter(char c);
    bool mouseHoveringOnField();
};

class TextLabel : public WindowElement
{
public:
    TextLabel(const char *text);

    void addBackground(Color bgColor, int padding = 5);
    void removeBackground();
    void draw() override;

private:
    const char *text;
    bool background = false;
    Color bgColor;
    int padding = 5;
};

enum MSG_TYPE
{
    ERROR,
    INFO,
    ASK
};

int PopUpWindow(Rectangle box, const char *msg, const char *title, int type);

double stringToDouble(const char *string);

#endif