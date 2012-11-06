#pragma once

#include "Entity.h"
#include "Animation.h"

class Game;
class Graphics;

class Enemy : public Entity {
public:
    Enemy(Vector2f pos = Vector2f());

    virtual void think(Game& game);
    virtual void draw(Game& game, Graphics& graphics);

    void destroy(Game& game);

    Animation animation;
};

