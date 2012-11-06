#pragma once

#include <string>

#include <SDL.h>

using namespace std;

class Texture {
public:
    friend class Graphics;
    Texture(const char* path);
    ~Texture();

    void bind();

    int getWidth() { return width; }
    int getHeight() { return height; }
    string& getSource() { return source; }

    static Texture& getTexture(const char* path);

private:
    string source;
    SDL_Surface* surface;
    unsigned int glname;
    bool bound;
    bool loadedToHw;
    unsigned int width;
    unsigned int height;
};

Texture* findTexture(const char* path);