#include "Animation.h"

#include "Sprite.h"
#include "Game.h"

Animation::Animation(void) : flip(false), currentFrame(0), time(0), over(false) {

}

Animation& Animation::operator+=(Sprite& sprite) {
    sprites.push_back(sprite);
    return *this;
}

void Animation::update() {
    time += TPS;
    if (time >= sprites[currentFrame].delay) {
        currentFrame++;
        if (currentFrame >= sprites.size()) {
            currentFrame = 0;
            over = true;
        }
        time = 0;
    }
}

void Animation::reset() {
    currentFrame = 0;
    time = 0;
    over = false;
}