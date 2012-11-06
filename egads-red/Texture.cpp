#include "Texture.h"

#include <vector>

#include <SDL_opengl.h>
#include <SDL_image.h>

Texture* boundTexture = 0;

vector<Texture*> textures;

// private functions

Texture::Texture(const char* path) : bound(false), loadedToHw(false), glname(0), source(path), surface(0), width(0), height(0) {
    // load image
    surface = IMG_Load(path);
    
    if (surface == 0) {
        throw exception("surface is null");
    }

    width = surface->w;
    height = surface->h;
}

Texture::~Texture(void) {
    if (bound) {
        glBindTexture(GL_TEXTURE_2D, 0);
        boundTexture = 0;
    }

    if (loadedToHw) {
        glDeleteTextures(1, &glname);
    }

    SDL_FreeSurface(surface);
}

void Texture::bind() {
    int internal_format = 0;
    int pixel_format = 0;
    int rmask, gmask, bmask, amask;

    if (bound) {
        return;
    }

    if (!loadedToHw) {
        // assuming surface isn't null...
        if (surface == 0) {
            throw exception("surface is null");
        }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        // then load into the hw
        // TODO do that
        glGenTextures(1, &glname);
        glBindTexture(GL_TEXTURE_2D, glname);

        SDL_Surface* surf;
        switch (surface->format->BitsPerPixel) {
        case 24:
            internal_format = 3;
            pixel_format = GL_RGB;
            break;
        case 32:
            internal_format = 4;
            pixel_format = GL_RGBA;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, surface->w, surface->h, 0, pixel_format, GL_UNSIGNED_BYTE, surface->pixels);
        loadedToHw = true;
    }

    if (boundTexture != 0) {
        boundTexture->bound = false;
    }

    glBindTexture(GL_TEXTURE_2D, glname);
    boundTexture = this;
    bound = true;
}

Texture* findTexture(const char* path) {
    Texture* tex;
    for (vector<Texture*>::iterator itr = textures.begin(); itr != textures.end(); itr++) {
        if ((*itr)->getSource() == path) {
            return (*itr);
        }
    }

    tex = new Texture(path);
    textures.push_back(tex);
    return tex;
}
