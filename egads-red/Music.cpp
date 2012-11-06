#include "Music.h"

#include <exception>
#include <iostream>

using namespace std;

Music* playingmusic = 0;

Music::Music(const char* path) : playing(false) {
    mus = Mix_LoadMUS(path);
    if (mus == 0) {
        cout << SDL_GetError() << endl;
        throw exception("failed to load music");
    }
}


Music::~Music() {
    if (playingmusic == this) {
        Mix_HaltMusic();
        playingmusic = 0;
    }
    Mix_FreeMusic(mus);
}

void Music::play() {
    playing = true;
    playingmusic = this;
    Mix_PlayMusic(mus, -1);
}
