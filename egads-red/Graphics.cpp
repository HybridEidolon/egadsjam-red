#include "Graphics.h"

#include <SDL_opengl.h>

#include "Rect.h"
#include "Texture.h"
#include "Sprite.h"

Graphics::Graphics() : color(1, 1, 1, 1) {
    _setGlColor();
}

void Graphics::setColor(const Color& c) {
    color = c;
    _setGlColor();
}

void Graphics::drawRect(float x, float y, float w, float h) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    fillRect(x, y, w, h);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Graphics::drawRect(const Rect& r) {
    drawRect(r.position.x, r.position.y, r.extents.x, r.extents.y);
}

void Graphics::fillRect(float x, float y, float w, float h, bool flip) {
    static float verts[8] = {0, 0, 0, 1, 1, 1, 1, 0};
    static float tex[8] = {0, 0, 0, 1, 1, 1, 1, 0};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, tex);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    _translateVector();
    glTranslatef(x, y, 0);
    glScalef(w, h, 1);
    if (flip) {
        glScalef(-1, 1, 1);
    }
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Graphics::fillRect(const Rect& r) {
    fillRect(r.position.x, r.position.y, r.extents.x, r.extents.y);
}

void Graphics::drawTexture(float x, float y, Texture& texture) {
    glEnable(GL_TEXTURE_2D);

    // blend
    if (texture.surface->format->BitsPerPixel == 32) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }

    texture.bind();
    fillRect(x, y, texture.getWidth(), texture.getHeight());
    glDisable(GL_TEXTURE_2D);
}

void Graphics::drawSprite(float x, float y, Sprite& sprite, bool flip) {
    glEnable(GL_TEXTURE_2D);

    // blend
    if (sprite.src.surface->format->BitsPerPixel == 32) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }

    sprite.src.bind();
    Vector2f real = sprite.getRealDimensions();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(sprite.position.x, sprite.position.y, 0);
    glScalef(sprite.dimensions.x, sprite.dimensions.y, 1);
    fillRect(x, y, real.x, real.y, flip);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
}

void Graphics::_setGlColor() {
    if (color.a < 1) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
    glColor4f(color.r, color.g, color.b, color.a);
}

void Graphics::_translateVector() {
    glTranslatef(translation.x, translation.y, 0);
}