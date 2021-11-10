#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

enum ButtonState { BTN_IDLE = 0, BTN_HOVER = 1 };

class Button 
{

private:
    Text displayText;
    Color buttonColor;
    Color HoverColor;
    Color TextColor = Color::White;
    Vector2f position;
    RectangleShape rect;
    ButtonState state;
    Sprite sprite;
    int ID;
    int focus;
    int textHoverSize = 5;

public:
    Button();
    Button(Color, Color, Color, Vector2f, Vector2f, string);
    void setHoverColor(Color c) {
        HoverColor = c;
    }
    void setColor(Color color);
    void setText(string text);
    void setText(string text, int size);
    void setText(string text, int size, Color color);
    void OnFocused();
    void OffFocused();
    void Update(RenderWindow &window);
    void setPosition(Vector2f);
    int isClicked(Vector2f pos);
    void setSize(Vector2f size);
    int MenuClick(Vector2f mousepos);
    void ImageLoad(string);
    FloatRect GlobalBounds() { return rect.getGlobalBounds(); };
    int getID();
    void setID(int);
    void addTextOffset(Vector2f);
    int getFocus() {
        return focus;
    }
    void setTextHoverSize(int size) {
        textHoverSize = size;
    }
};