#include "Game.h"

#include <iostream>

#include <SDL_opengl.h>
#include <SDL_mixer.h>

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Music.h"

using namespace std;

Game::Game() : running(false), initialized(false), numEntities(0), first(0), last(0), keys() {
    for (int i = 0; i < MAX_KEYS; i++) {
        keys[i] = false;
    }
}

Game::~Game() {
    //entities.remove_if( [](Entity* element) { delete element; return true;} );
    //for (EntityList::iterator it = entities.begin(); it != entities.end(); it++) {
    //    delete *it;
    //}
    Entity* itr = first;

    while (itr != 0) {
        Entity* next = itr->next;
        delete itr;
        itr = next;
    }

    Mix_CloseAudio();
    SDL_Quit();
}

void Game::init() {
    running = true;

    // init sdl
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
    
    SDL_putenv("SDL_VIDEO_CENTERED=center");

    surface = SDL_SetVideoMode(640, 400, 32, SDL_OPENGL);
    if (surface == 0) {
        throw exception("failed to set video mode");
    }
    SDL_WM_SetCaption("EGaDS! Red Blade", 0);

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0) {
        throw exception("failed to initialize sdl_mixer");
    }

    // init game
    tilemap = new TileMap(32, 32);

    for (int i = 0; i < 29; i++) {
        tilemap->set(Tile(i, 12, true, 2));
    }
    tilemap->set(Tile(29, 12, true, 3));
    for (int i = 0; i < 30; i++) {
        tilemap->set(Tile(i, 13, true, 1));
    }
    for (int i = 0; i < 30; i++) {
        tilemap->set(Tile(i, 14, true, 1));
    }
    for (int i = 0; i < 30; i++) {
        tilemap->set(Tile(i, 15, true, 1));
    }
    for (int i = 0; i < 30; i++) {
        tilemap->set(Tile(i, 16, true, 1));
    }
    for (int i = 0; i < 30; i++) {
        tilemap->set(Tile(i, 17, true, 1));
    }
    for (int i = 0; i < 30; i++) {
        tilemap->set(Tile(i, 18, true, 1));
    }

    tilemap->set(Tile(0, 11, true, 1));
    tilemap->set(Tile(0, 10, true, 1));
    tilemap->set(Tile(0, 9, true, 1));
    tilemap->set(Tile(0, 8, true, 1));
    tilemap->set(Tile(0, 7, true, 3));

    // ents
    addEntity(new Player(Vector2f(128, 80)));
    addEntity(new Enemy(Vector2f(100-16, 200-16)));
    addEntity(new Enemy(Vector2f(200-16, 200-16)));
    addEntity(new Enemy(Vector2f(300-16, 200-16)));
    addEntity(new Enemy(Vector2f(400-16, 200-16)));
    addEntity(new Enemy(Vector2f(500-16, 200-16)));
    addEntity(new Enemy(Vector2f(600-16, 200-16)));

    Music* m = new Music("data/mus/mus.ogg");
    m->play();

    initialized = true;
}

void Game::addEntity(Entity* ent) {
    if (first == 0) {
        first = ent;
        last = ent;
        numEntities = 1;
        return;
    }

    ent->previous = last;
    last->next = ent;
    last = ent;
    numEntities++;
}

void Game::run() {
    uint32_t before;
    uint32_t after;
    SDL_Event evt;

    while (running) {
        before = SDL_GetTicks();

        // handle SDL events
        events();

        if (!running) break;

        update();
        draw();

        SDL_GL_SwapBuffers();

        after = SDL_GetTicks();

        if (after - before < (1000/60)) {
            SDL_Delay(1000/60 - (after - before));
        }
    }
}

void Game::update() {
    Entity* itr = first;
    int count = 0;

    while (itr != 0) {
        if (itr->deleteMe) {
            if (first == itr) {
                first = itr->next;
                itr->next->previous = 0;
            } else if (last == itr) {
                last = itr->previous;
                itr->previous->next = 0;
            } else {
                itr->previous->next = itr->next;
                itr->next->previous = itr->previous;
            }
            numEntities--;
            itr = itr->next;
            continue;
        }

        itr->think(*this);
        itr = itr->next;
    }
}

void Game::draw() {
    Entity* itr = first;

    if (-graphics.translation.x < 0) graphics.translation.x = 0;
    if (-graphics.translation.y < 0) graphics.translation.y = 0;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 320, 200, 0, -1, 1);

    tilemap->draw(graphics);

    while (itr != 0) {
        itr->draw(*this, graphics);

        itr = itr->next;
    }
}

void Game::events() {
    SDL_Event evt;

    while (SDL_PollEvent(&evt)) {
        int key = -42;
        switch (evt.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch (evt.key.keysym.sym) {
            case SDLK_UP:
                key = UP;
                break;
            case SDLK_DOWN:
                key = DOWN;
                break;
            case SDLK_LEFT:
                key = LEFT;
                break;
            case SDLK_RIGHT:
                key = RIGHT;
                break;
            case SDLK_z:
                key = JUMP;
                break;
            case SDLK_x:
                key = SLASH;
                break;
            case SDLK_RETURN:
                key = START;
                break;
            case SDLK_ESCAPE:
                key = QUIT;
                break;
            }
            if (key != -42) keys[key] = true;
            break;
        case SDL_KEYUP:
            switch (evt.key.keysym.sym) {
            case SDLK_UP:
                key = UP;
                break;
            case SDLK_DOWN:
                key = DOWN;
                break;
            case SDLK_LEFT:
                key = LEFT;
                break;
            case SDLK_RIGHT:
                key = RIGHT;
                break;
            case SDLK_z:
                key = JUMP;
                break;
            case SDLK_x:
                key = SLASH;
                break;
            case SDLK_RETURN:
                key = START;
                break;
            case SDLK_ESCAPE:
                running = false;
                key = QUIT;
                break;
            }
            if (key != -42) keys[key] = false;
            break;
        }
    }
}