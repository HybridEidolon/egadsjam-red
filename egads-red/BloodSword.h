#pragma once

#include "Animation.h"
#include "Entity.h"
#include "Sound.h"

class Player;

class BloodSword : public Entity {
public:
    BloodSword(Player& parent, Vector2f pos, bool flip = false);

    virtual void think(Game& game);
    virtual void draw(Game& game, Graphics& graphics);

    Sound sound;
    Animation animation;
    Player& parent;
    bool played;
};

