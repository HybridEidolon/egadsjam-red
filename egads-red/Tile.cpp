#include "Tile.h"

#include <iostream>

#include "Rect.h"

using namespace std;

Tile::Tile(unsigned int x, unsigned int y, bool solid, uint8_t tileIndex) : x(x), y(y), solid(solid), tileIndex(tileIndex) {
    
}

Tile::~Tile() {
    
}

Rect Tile::rect() {
    return Rect(Vector2f((x*16) + 8, (y*16) + 8), Vector2f(8, 8));
}
