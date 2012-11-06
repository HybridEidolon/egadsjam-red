#pragma once

#include <string>

#include "Vector2f.h"
#include "Tile.h"

#define TYPE(name) type = name

using namespace std;

class Rect;
class Game;
class Graphics;

class Entity {
public:
    friend class Game;
    Entity(Vector2f pos = Vector2f(), Vector2f extents = Vector2f());

    Vector2f position;
    Vector2f extents;

    bool collidable;
    bool deleteMe;
    string type;

    Rect rect();

    virtual void think(Game& game) = 0;
    virtual void draw(Game& game, Graphics& g) = 0;

    Entity* next;
    Entity* previous;
};
