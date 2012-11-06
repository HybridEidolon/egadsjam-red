#pragma once

#include "Vector2f.h"
#include "Color.h"

class Rect;
class Texture;
class Sprite;

class Graphics {
public:
    Graphics();

    void setColor(const Color& c);
    void drawRect(float x, float y, float w, float h);
    void drawRect(const Rect& r);
    void fillRect(float x, float y, float w, float h, bool flip = false);
    void fillRect(const Rect& r);
    void drawTexture(float x, float y, Texture& texture);
    void drawTexture(float x, float y, float w, float h, unsigned int glName);
    void drawSprite(float x, float y, Sprite& sprite, bool flip);

    Vector2f translation;

private:
    void _setGlColor();
    void _translateVector();
    Color color;
};
