#pragma once

#include <SDL_mixer.h>

class Music {
public:
    Music(const char* path);
    ~Music();

    void play();

    Mix_Music* mus;
    bool playing;
};

