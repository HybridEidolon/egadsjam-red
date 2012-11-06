#include "Giblet.h"

#include "Texture.h"
#include "Graphics.h"
#include "Game.h"
#include "Rect.h"
#include "Sound.h"

Sound* bounce = 0;

Giblet::Giblet(Vector2f pos, Vector2f velocity) : Entity(pos, Vector2f(4, 4)), velocity(velocity), life(2) {
    TYPE("Giblet");

    if (bounce == 0) {
        bounce = new Sound("data/wav/giblet-bounce.wav");
    }
}

void Giblet::think(Game& game) {
    velocity.y += 10;
    life -= TPS;
    
    // apply velocity
    position += velocity * TPS;

    // do collisions
    Vector2f c = game.tilemap->collide(rect());

    if (c.length() > 0) {
        position += c;
        if (c.x != 0) {
            velocity.x = -velocity.x;
        }
        if (c.y != 0) {
            velocity.y = -velocity.y;
        }
        bounce->play();
    }

    if (life <= 0) {
        deleteMe = true;
    }
}

void Giblet::draw(Game& game, Graphics& graphics) {
    graphics.drawTexture(position.x - 4, position.y - 4, *findTexture("data/img/giblet.png"));
}
