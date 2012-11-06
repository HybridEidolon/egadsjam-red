#pragma once

#include <vector>

using namespace std;

class Sprite;

class Animation {
public:
    Animation(void);
    
    void update();
    void reset();

    bool flip;
    vector<Sprite> sprites;
    Animation& operator+=(Sprite& sprite);
    int currentFrame;
    float time;
    bool over;
};
