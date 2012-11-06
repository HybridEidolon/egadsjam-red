#pragma once

#include <SDL_mixer.h>

class Sound {
public:
    Sound(const char* sound);
    ~Sound();

    void play();
    Mix_Chunk* sample;
};

