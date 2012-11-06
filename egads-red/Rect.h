#pragma once

#include "Vector2f.h"

class Rect {
public:
    Rect(Vector2f pos = Vector2f(), Vector2f ext = Vector2f());

    Vector2f position;
    Vector2f extents;

    bool isOverlapping(Rect other);
    Vector2f collide(Rect other);

    float minX() { return position.x - extents.x; }
    float maxX() { return position.x + extents.x; }
    float minY() { return position.y - extents.y; }
    float maxY() { return position.y + extents.y; }

    Vector2f min();
    Vector2f max();
};

