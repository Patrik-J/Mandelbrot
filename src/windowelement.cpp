#ifndef windowelement_cpp
#define windowelement_cpp

#include "windowelement.hpp"

void WindowElement::setFont(int fontSize, Font font, float spacing)
{
    this->fontSize = fontSize;
    this->font = font;
    this->spacing = spacing;
};

void WindowElement::setTextColor(Color color)
{
    this->textColor = color;
};

void WindowElement::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
};

void WindowElement::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
};

TextButton::TextButton() {};

TextButton::TextButton(int width, int height)
{
    this->width = width;
    this->height = height;
};

void TextButton::setText(const char *text, int fontSize, Color textColor, float spacing, Font font)
{
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->spacing = spacing;
    this->font = font;
};

void TextButton::setText(const char *text)
{
    this->text = text;
};

void TextButton::setBackgroundColor(Color bgColor)
{
    this->bgColor = bgColor;
};

void TextButton::makeHoverable(Color bgHoverColor, Color textHoverColor)
{
    this->bgHoverColor = bgHoverColor;
    this->textHoverColor = textHoverColor;
    this->hoverable = true;
};

void TextButton::unmakeHoverable()
{
    this->hoverable = false;
};

bool TextButton::mouseOverButton()
{
    Vector2 mousePos = GetMousePosition();

    int topLeftCorner_X = this->x - this->width / 2;
    int topLeftCorner_Y = this->y - this->height / 2;

    int bottomRightCorner_X = this->x + this->width / 2;
    int bottomRightCorner_Y = this->y + this->height / 2;

    if ((mousePos.x >= topLeftCorner_X && mousePos.x <= bottomRightCorner_X) && ((mousePos.y >= topLeftCorner_Y && mousePos.y <= bottomRightCorner_Y)))
    {
        return true;
    }
    return false;
};

bool TextButton::mouseClickedOnButton()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->mouseOverButton())
    {
        return true;
    }
    return false;
};

void TextButton::setAction(std::function<void(void)> action)
{
    this->action = action;
};

void TextButton::highlight(bool highlight)
{
    if (highlight)
    {
        this->activeBg = bgHoverColor;
        this->activeText = textHoverColor;
    }
    else
    {
        this->activeBg = bgColor;
        this->activeText = textColor;
    }
};

void TextButton::setRoundness(bool roundedCorners, float roundness, int segments)
{
    this->rounded = roundedCorners;
    this->roundness = roundness;
    this->segments = segments;
};

void TextButton::draw()
{
    if (this->hoverable)
    {
        this->highlight(this->mouseOverButton());
    }

    if (this->rounded)
    {
        Rectangle rec = Rectangle{
            (float)this->x - this->width / 2,
            (float)this->y - this->height / 2,
            (float)this->width,
            (float)this->height};
        DrawRectangleRounded(rec, this->roundness, this->segments, bgColor);
    }
    else
    {
        DrawRectangle(this->x - this->width / 2, this->y - this->height / 2, this->width, this->height, this->activeBg);
    }

    Vector2 textSize = MeasureTextEx(this->font, this->text, this->fontSize, this->spacing);

    Vector2 textPosition = {
        this->x - (textSize.x / 2.0f),
        this->y - (textSize.y / 2.0f)};

    DrawTextEx(this->font, this->text, textPosition, this->fontSize, this->spacing, this->activeText);

    if (this->mouseClickedOnButton())
    {
        this->action();
    };
};

TextField::TextField()
{
    this->last_char = 0;
    this->setCharLimit();
    this->text = new char[this->max_len + 1];
    this->clearBuffer();
};

TextField::TextField(int width, int height)
{
    this->width = width;
    this->height = height;
    this->last_char = 0;
    this->setCharLimit();
    this->text = new char[this->max_len + 1];
    this->clearBuffer();
};

void TextField::readUserInput()
{
    int key = GetCharPressed();
    while (key > 0)
    {
        if (this->only_numbers)
        {
            if ((key >= 48 && key <= 57) || (key == 46))
            {
                this->writeUserInput((char)key);
            }
        }
        else
        {
            this->writeUserInput((char)key);
        }
        key = GetCharPressed();
    }

    if (IsKeyDown(KEY_BACKSPACE) && this->last_char > 0)
    {
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (IsKeyDown(KEY_LEFT_CONTROL))
            {
                this->clearBuffer();
                this->last_char = 0;
            }
            else
            {
                this->last_char--;
                this->text[this->last_char] = '\0';
                WaitTime(0.01);
            }
        }
    }
};

void TextField::writeUserInput(char c)
{
    if (this->last_char < this->max_len - 1)
    {
        this->text[this->last_char] = c;
        this->last_char++;
        this->text[this->last_char] = STRING_TERMINATE;
    }
};

void TextField::writeTextToTextField()
{
    if (this->last_char == 0 && !this->fieldActivated)
        return;

    if (this->fieldActivated)
    {
        char *_text = this->getText();

        // check if the text overflows
        Vector2 size = MeasureTextEx(this->font, _text, this->fontSize, this->spacing);

        int start_index = 0;

        while ((int)size.x > (this->width - 2 * this->xOffset) && start_index < this->last_char)
        {
            start_index++;
            size = MeasureTextEx(this->font, _text + start_index, this->fontSize, this->spacing);
        }

        if (this->blinking_cursor)
        {
            this->time_since_last_frame += GetFrameTime();
            if (this->time_since_last_frame >= CURSOR_TIME)
            {
                this->show_cursor = !this->show_cursor;
                this->time_since_last_frame = 0.0f;
            }
        };

        char *text;

        if (this->show_cursor)
        {
            text = new char[this->last_char + 2];
            memcpy(text, _text, this->last_char);
            text[this->last_char] = this->cursor_char;
            text[this->last_char + 1] = STRING_TERMINATE;
        }
        else
        {
            text = _text;
        }

        DrawTextEx(this->font, text + start_index, {this->textBox.x + this->xOffset, this->textBox.y + this->yOffset}, this->fontSize, this->spacing, this->textColor);
    }
    else
    {
        char *text = this->getText();

        // check if the text overflows
        Vector2 size = MeasureTextEx(this->font, text, this->fontSize, this->spacing);

        int start_index = 0;

        while ((int)size.x > (this->width - 2 * this->xOffset) && start_index < this->last_char)
        {
            start_index++;
            size = MeasureTextEx(this->font, text + start_index, this->fontSize, this->spacing);
        }

        DrawTextEx(this->font, text + start_index, {this->textBox.x + this->xOffset, this->textBox.y + this->yOffset}, this->fontSize, this->spacing, this->textColor);
    }
};

void TextField::clearBuffer()
{
    for (int i = 0; i < max_len; i++)
    {
        this->text[i] = STRING_TERMINATE;
    }
};

bool TextField::validCharacter(char c)
{
    int key = c;
    if (key >= 32 && key <= 126)
    {
        return true;
    }
    return false;
};

void TextField::setColor(Color textColor, Color bgColor, Color borderColor, Color borderHoverColor)
{
    this->textColor = textColor;
    this->bgColor = bgColor;
    this->borderColor = borderColor;
    this->borderHoverColor = borderHoverColor;
};

bool TextField::mouseHoveringOnField()
{
    Vector2 mousePos = GetMousePosition();
    float topLeftCorner_X = this->x - this->width / 2.0f;
    float topLeftCorner_Y = this->y - this->height / 2.0f;
    float bottomRightCorner_X = this->x + this->width / 2.0f;
    float bottomRightCorner_Y = this->y + this->height / 2.0f;

    if ((mousePos.x >= topLeftCorner_X && mousePos.x <= bottomRightCorner_X) && ((mousePos.y >= topLeftCorner_Y && mousePos.y <= bottomRightCorner_Y)))
    {
        return true;
    }
    return false;
};

void TextField::checkActivation()
{

    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool hovering = this->mouseHoveringOnField();

    if (clicked && !hovering)
    {
        // user clicked on something else -> not activated
        this->fieldActivated = false;
    }
    else if (!clicked && !hovering)
    {
        // user did not do anything -> if (not) activated, stay the same
    }
    else if (clicked && hovering)
    {
        // user clicked on the field
        this->fieldActivated = true;
    }
    return;
};

char *TextField::getText()
{
    return this->text;
};

void TextField::setTextOffset(int x, int y)
{
    this->xOffset = x;
    this->yOffset = y;
};

void TextField::setCharLimit(int lim)
{
    this->max_len = lim;
};

void TextField::setNumberField(bool onlyNumbers)
{
    this->only_numbers = onlyNumbers;
};

void TextField::draw()
{
    this->textBox = Rectangle{
        this->x - this->width / 2.0f,
        this->y - this->height / 2.0f,
        (float)this->width,
        (float)this->height};

    DrawRectangleRec(textBox, this->bgColor);
    bool mouseOnText = this->mouseHoveringOnField();
    this->checkActivation();

    if (mouseOnText || this->fieldActivated)
        DrawRectangleLinesEx(this->textBox, this->border_width, this->borderHoverColor);
    else
        DrawRectangleLinesEx(this->textBox, this->border_width, this->borderColor);

    if (this->fieldActivated)
    {
        this->readUserInput();
    }
    this->writeTextToTextField();
};

void TextField::setBorderWidth(int width)
{
    this->border_width = width;
};

void TextField::blinkCursor(bool blink, char c)
{
    this->blinking_cursor = blink;
    this->cursor_char = c;
};

TextLabel::TextLabel(const char *text)
{
    this->text = text;
};

void TextLabel::addBackground(Color bgColor, int padding)
{
    this->bgColor = bgColor;
    this->padding = padding;
    this->background = true;
};

void TextLabel::removeBackground()
{
    this->background = false;
}

void TextLabel::draw()
{
    Vector2 textSize = MeasureTextEx(this->font, this->text, this->fontSize, this->spacing);

    if (this->background)
    {
        int left_x = this->x - textSize.x / 2 - this->padding;
        int top_y = this->y - textSize.y / 2 - this->padding;
        int width = textSize.x + 2 * this->padding;
        int height = textSize.y + 2 * this->padding;
        DrawRectangle(left_x, top_y, width, height, this->bgColor);
    }
    Vector2 pos = {
        (float)(this->x - textSize.x / 2),
        (float)(this->y - textSize.y / 2)};
    DrawTextEx(this->font, this->text, pos, this->fontSize, this->spacing, this->textColor);
};

int PopUpWindow(Rectangle box, const char *msg, const char *title, int type)
{
    int result = -1;
    int width = 150, height = 50;

    // text message
    Vector2 textSize = MeasureTextEx(GetFontDefault(), msg, 30, 2.0);
    if (textSize.x > box.width)
    {
        box.x = box.x + box.width / 2.0f;
        box.width = textSize.x + 40.0f;
        box.x = box.x - box.width / 2.0f;
    }
    DrawRectangleRec(box, RAYWHITE);

    Vector2 textPos = {
        box.x + (box.width / 2.0f) - (textSize.x / 2.0f),
        box.y + (box.height / 2.0f) - (textSize.y / 2.0f)};

    DrawTextEx(GetFontDefault(), msg, textPos, 30, 2.0, BLACK);

    // close button and title bar
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), title, 26, 2.0);
    DrawRectangle(box.x, box.y, box.width, titleSize.y * 1.3, GRAY);
    DrawText(title, box.x + 0.1 * titleSize.x, box.y + 0.15 * titleSize.y, 26, BLACK);
    TextButton close = TextButton(titleSize.y * 1.3, titleSize.y * 1.3);
    close.setText("X");
    close.setFont(26);
    close.makeHoverable(BLACK, WHITE);
    close.setBackgroundColor(RED);
    close.setTextColor(WHITE);
    close.setPosition(box.x + box.width - titleSize.y * 1.3 / 2, box.y + titleSize.y * 1.3 / 2);
    close.setAction([&]()
                    { result = 1; });
    close.draw();

    // confirm button
    TextButton ok = TextButton(width, height);
    ok.setText("Ok");
    ok.setAction([&]()
                 { result = 1; });
    ok.setFont(26);
    ok.setTextColor(WHITE);
    ok.setBackgroundColor(GRAY);
    ok.makeHoverable(BLACK, WHITE);
    ok.setPosition(box.x + box.width / 2, box.y + 3 * box.height / 4);
    ok.draw();

    return result;
};

double stringToDouble(const char *string)
{
    double value = std::stod(string);
    return value;
};

#endif