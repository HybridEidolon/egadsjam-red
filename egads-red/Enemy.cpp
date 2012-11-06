#include "Enemy.h"

#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Graphics.h"
#include "Giblet.h"
#include "Rect.h"
#include "Sound.h"

Sound* dead = 0;


Enemy::Enemy(Vector2f pos) : Entity(pos, Vector2f(8, 8)), animation() {
    TYPE("Enemy");
    extents = Vector2f(8, 8);
    Texture* tex = findTexture("data/img/enemy.png");
    float speed = .05f;
    animation += Sprite(*tex, Vector2f(0, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.125f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.25f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.375f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.5f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.625f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.75f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.875f, 0), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(0, .5f), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.125f, .5f), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.25f, .5f), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.375f, .5f), Vector2f(.125f, .5f), speed);
    animation += Sprite(*tex, Vector2f(.5f, .5f), Vector2f(.125f, .5f), speed);

    if (dead == 0) {
        dead = new Sound("data/wav/enemy-die.wav");
    }
}

void Enemy::think(Game& game) {
    // collide with bloodswords
    Entity* itr = game.getFirst();

    while (itr != 0) {
        if (itr->type == "BloodSword") {
            // break it!
            if (itr->rect().isOverlapping(rect())) {
                destroy(game);
                return;
            }
        }
        itr = itr->next;
    }

    animation.update();
}

void Enemy::destroy(Game& game) {
    for (int i = 0; i < 32; i++) {
        Vector2f v = Vector2f(((float)rand() / RAND_MAX) * 128 - 64, -256 + (((float)rand() / RAND_MAX) * 128 - 64));
        game.addEntity(new Giblet(position, v));
    }

    dead->play();
    deleteMe = true;
}

void Enemy::draw(Game& game, Graphics& graphics) {
    graphics.drawSprite(position.x - 8, position.y - 8, animation.sprites[animation.currentFrame], false);
}
