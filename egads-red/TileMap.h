#pragma once

using namespace std;

class Tile;
class Graphics;
class Vector2f;
class Rect;
class Texture;

class TileMap {
public:
    TileMap(unsigned int width, unsigned int height);
    TileMap(const TileMap& copy);
    ~TileMap(void);

    void set(Tile tile);
    Tile get(float x, float y);
    Tile getIndex(int x, int y);

    void draw(Graphics& graphics);
    Vector2f collide(Rect rect);
    int indexOf(int x, int y);

    unsigned int width;
    unsigned int height;
    Texture* tex;
private:
    Tile* tiles;
};
