#include "Sprite.h"

#include "Texture.h"

Sprite::Sprite(Texture& src, Vector2f position, Vector2f dimensions, float delay) : src(src), position(position), dimensions(dimensions), delay(delay) {

}

Vector2f Sprite::getRealDimensions() {
    return Vector2f(dimensions.x * src.getWidth(), dimensions.y * src.getHeight());
}
