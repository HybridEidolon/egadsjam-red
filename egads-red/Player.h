#pragma once

#include "Entity.h"

#include "Sprite.h"
#include "Animation.h"

class Game;
class Graphics;

class Player : public Entity {
public:
    friend class BloodSword;
    Player(Vector2f pos = Vector2f());

    virtual void think(Game& game);
    virtual void draw(Game& game, Graphics& graphics);

    Vector2f velocity;
    Animation* currentAnimation;
    bool onground;
    bool jumping;
    bool slashing;

    Animation animStanding;

};

