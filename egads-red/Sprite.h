#pragma once

#include "Vector2f.h"

class Texture;

class Sprite {
public:
    Sprite(Texture& src, Vector2f position = Vector2f(), Vector2f dimensions = Vector2f(1, 1), float delay = 0);

    Vector2f getRealDimensions();

    Texture& src;
    Vector2f position;
    Vector2f dimensions;
    float delay;
};

