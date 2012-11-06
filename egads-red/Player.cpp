#include "Player.h"

#include <iostream>

#include "Game.h"
#include "Graphics.h"
#include "Texture.h"
#include "Rect.h"
#include "BloodSword.h"
#include "Sound.h"

Sound* jump = 0;

Player::Player(Vector2f pos) : Entity(pos), velocity(), animStanding(), currentAnimation(0), onground(false), jumping(false), slashing(false) {
    TYPE("Player");
    extents = Vector2f(8, 8);
    Texture* t = findTexture("data/img/player.png");
    animStanding += Sprite(*t, Vector2f(0, 0), Vector2f(.5f, .5f), .2f);
    animStanding += Sprite(*t, Vector2f(.5, 0), Vector2f(.5f, .5f), .2f);
    animStanding += Sprite(*t, Vector2f(0, .5), Vector2f(.5f, .5f), .2f);

    currentAnimation = &animStanding;

    if (jump == 0) {
        jump = new Sound("data/wav/jump.wav");
    }
}

void Player::think(Game& game) {
    velocity.y += 10;

    Vector2f move = Vector2f();

    if (game.keys[LEFT]) {
        currentAnimation->flip = true;
        move.x -= 1;
    }
    if (game.keys[RIGHT]) {
        currentAnimation->flip = false;
        move.x += 1;
    }

    move *= 64;
    velocity.x = move.x;

    // jumping
    if (onground && !jumping && game.keys[JUMP]) {
        jumping = true;
        onground = false;
        velocity.y -= 300;
        jump->play();
    }

    if (!game.keys[JUMP]) {
        if (jumping && velocity.y < -32) {
            velocity.y = -32;
        }
        jumping = false;
    }

    // add velocity scaled
    position += velocity * TPS;

    onground = false;
    // ----COLLISION----
    // tiles
    Vector2f trans = game.tilemap->collide(rect());
    position += trans;
    if (trans.y != 0) {
        velocity.y = 0;
        onground = true;
    }

    // ----SLASHING----
    if (game.keys[SLASH] && !slashing) {
        Vector2f add = Vector2f(0, -8.f);
        if (currentAnimation->flip) {
            add.x = -8;
        } else {
            add.x = 8;
        }

        game.addEntity(new BloodSword(*this, position + add, currentAnimation->flip));
        slashing = true;
    }
    
    if (!game.keys[SLASH]) {
        slashing = false;
    }

    // set graphics translation
    Graphics& g = game.getGraphics();

    g.translation.x = -position.x + 160;
    g.translation.y = -position.y + 100;

    // update curanim
    currentAnimation->update();
}

void Player::draw(Game& game, Graphics& graphics) {
    if (currentAnimation->flip) {
        graphics.drawSprite(position.x + 8, position.y - 8, currentAnimation->sprites[currentAnimation->currentFrame], true);
    } else {
        graphics.drawSprite(position.x - 8, position.y - 8, currentAnimation->sprites[currentAnimation->currentFrame], false);
    }
}
