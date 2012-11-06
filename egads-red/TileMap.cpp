#include "TileMap.h"

#include <exception>
#include <new>
#include <cmath>
#include <iostream>

#include "Tile.h"
#include "Graphics.h"
#include "Rect.h"
#include "Vector2f.h"
#include "Rect.h"
#include "Sprite.h"
#include "Texture.h"

using namespace std;

TileMap::TileMap(unsigned int width, unsigned int height) : width(width), height(height) {
    tiles = new Tile[this->width * this->height];
}

TileMap::TileMap(const TileMap& copy) {
    delete[] tiles;
    width = copy.width;
    height = copy.height;
    tiles = copy.tiles;
}

TileMap::~TileMap() {
    delete[] tiles;
}

void TileMap::set(Tile tile) {
    if (tile.x >= width || tile.y >= height) {
        throw exception("tile out of bounds");
    }

    tiles[indexOf(tile.x, tile.y)] = tile;
}

Tile TileMap::get(float x, float y) {
    if (x < 0 || y < 0 || x >= width * 16 || y >= height * 16) {
        return Tile();
    }

    return getIndex(floor(x / 16), floor(y / 16));
}

Tile TileMap::getIndex(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return Tile();
    }

    return tiles[indexOf(x, y)];
}

int TileMap::indexOf(int x, int y) {
    return (width * y) + x;
}

void TileMap::draw(Graphics& graphics) {
    Texture* tiles = findTexture("data/img/tiles.png");
    Sprite s = Sprite(*tiles, Vector2f(), Vector2f(1.f/16.f, 1.f/16.f));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Tile t = getIndex(x, y);
            if (t.tileIndex != 0) {
                s.position = Vector2f((float)(t.tileIndex % 16) / 16, (float)(t.tileIndex / 16) / 16);
                graphics.drawSprite(x*16, y*16, s, false);
            }
        }
    }

}

Vector2f TileMap::collide(Rect rect) {
    int minX = floorf(rect.minX() / 16) - 1;
    int minY = floorf(rect.minY() / 16) - 1;
    int maxX = floorf(rect.maxX() / 16) + 1;
    int maxY = floorf(rect.maxY() / 16) + 1;
    Rect local = Rect(rect);
    Vector2f result;
    Vector2f total = Vector2f();

    for (int y = (minY < 0 ? 0 : minY); y < maxY && y < height; y++) {
        for (int x = (minX < 0 ? 0 : minX); x < maxX && x < width; x++) {
            result = local.collide(getIndex(x, y).rect());
            
            local.position += result;
            total += result;
        }
    }

    return total;
}
