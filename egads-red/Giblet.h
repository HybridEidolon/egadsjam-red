#pragma once
#include "entity.h"

class Giblet : public Entity {
public:
    Giblet(Vector2f pos = Vector2f(), Vector2f velocity = Vector2f(0, -64));

    Vector2f velocity;
    float life;

    virtual void think(Game& game);
    virtual void draw(Game& game, Graphics& graphics);
};

