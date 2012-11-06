#include "Rect.h"

#include <iostream>
#include <cmath>

using namespace std;

Rect::Rect(Vector2f pos, Vector2f ext) : position(pos), extents(ext) {

}

bool Rect::isOverlapping(Rect other) {
    if (maxX() < other.minX() ||
        maxY() < other.minY() ||
        minX() > other.maxX() ||
        minY() > other.maxY()) {
        return false;
    } else {
        return true;
    }
}

Vector2f Rect::min() {
    return Vector2f(minX(), minY());
}

Vector2f Rect::max() {
    return Vector2f(maxY(), maxY());
}

Vector2f Rect::collide(Rect other) {
    // minimum axis translation vector
    // http://www.opentk.com/node/869
    Vector2f amin = min();
    Vector2f amax = max();
    Vector2f bmin = other.min();
    Vector2f bmax = other.max();
    Vector2f mtd = Vector2f();

    // base case
    if (!isOverlapping(other)) {
        return mtd;
    }

    float left = bmin.x - amax.x;
    float right = bmax.x - amin.x;
    float top = bmax.y - amin.y;
    float bottom = bmin.y - amax.y;

    if (abs(left) > right) {
        mtd.x = right;
    } else {
        mtd.x = left;
    }

    if (top < abs(bottom)) {
        mtd.y = top;
    } else {
        mtd.y = bottom;
    }

    if (abs(mtd.x) > abs(mtd.y)) {
        mtd.x = 0;
    } else {
        mtd.y = 0;
    }

    return mtd;
}
