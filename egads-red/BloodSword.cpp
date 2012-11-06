#include "BloodSword.h"

#include "Sprite.h"
#include "Texture.h"
#include "Graphics.h"
#include "Player.h"
#include "Sound.h"

BloodSword::BloodSword(Player& parent, Vector2f pos, bool flip) : Entity(pos, Vector2f(16, 16)), animation(), parent(parent), played(false), sound("data/wav/bloodsword.wav") {
    TYPE("BloodSword");
    // animation build
    Texture* tex;
    tex = findTexture("data/img/bloodswing-1.png");

    animation.flip = flip;

    animation += Sprite(*tex, Vector2f(0, 0), Vector2f(.25f, .5f), 0.03f);
    animation += Sprite(*tex, Vector2f(.25f, 0), Vector2f(.25f, .5f), 0.03f);
    animation += Sprite(*tex, Vector2f(.5f, 0), Vector2f(.25f, .5f), 0.03f);
    animation += Sprite(*tex, Vector2f(.75f, 0), Vector2f(.25f, .5f), 0.03f);
    animation += Sprite(*tex, Vector2f(0, .5f), Vector2f(.25f, .5f), 0.03f);
    animation += Sprite(*tex, Vector2f(.25f, .5f), Vector2f(.25f, .5f), 0.07f);
    animation += Sprite(*tex, Vector2f(.5f, .5f), Vector2f(.25f, .5f), 0.07f);
    animation += Sprite(*tex, Vector2f(.75f, .5f), Vector2f(.25f, .5f), 0.07f);
}

void BloodSword::think(Game& game) {
    if (!played) {
        sound.play();
        played = true;
    }
    if (animation.over) {
        deleteMe = true;
        return;
    }
    animation.update();
}

void BloodSword::draw(Game& game, Graphics& graphics) {
    if (deleteMe) {
        return;
    }
    if (animation.flip) {
        graphics.drawSprite(position.x + 16, position.y - 16, animation.sprites[animation.currentFrame], true);
    } else {
        graphics.drawSprite(position.x - 16, position.y - 16, animation.sprites[animation.currentFrame], false);
    }
}
