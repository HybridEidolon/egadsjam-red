#include "Sound.h"

#include <iostream>

using namespace std;

Sound::Sound(const char* path) {
    sample = Mix_LoadWAV(path);
    if (sample == 0) {
        throw exception(SDL_GetError());
    }
}


Sound::~Sound(void) {
    Mix_FreeChunk(sample);
}

void Sound::play() {
    Mix_PlayChannel(-1, sample, 0);
}