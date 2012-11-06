#pragma once

#include <SDL_stdinc.h>

class Rect;

class Tile {
public:
    Tile(unsigned int x = 0, unsigned int y = 0, bool solid = false, uint8_t tileIndex = 0);
    ~Tile();
    unsigned int x;
    unsigned int y;

    bool solid;
    uint8_t tileIndex;

    Rect rect();
};

