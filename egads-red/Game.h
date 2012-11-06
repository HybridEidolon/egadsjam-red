#pragma once

#include <SDL.h>

#include "Graphics.h"
#include "TileMap.h"

#define TPS .016f
#define MAX_ENTITIES 2048

using namespace std;

class Entity;

enum Keys {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    JUMP,
    SLASH,
    START,
    QUIT,
    MAX_KEYS
};

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();
    void update();
    void draw();
    void events();

    void addEntity(Entity* ent);
    Graphics& getGraphics() { return graphics; }
    Entity* getFirst() { return first; }

    bool running;
    TileMap* tilemap;
    bool keys[MAX_KEYS];

private:
    Entity* first;
    Entity* last;
    int numEntities;
    bool initialized;
    Graphics graphics;
    SDL_Surface* surface;
};
