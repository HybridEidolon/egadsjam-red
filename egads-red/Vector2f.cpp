#include "Vector2f.h"

#include <cmath>

Vector2f::Vector2f(float x, float y) : x(x), y(y) {

}

Vector2f::Vector2f(const Vector2f& c) : x(c.x), y(c.y) {

}

Vector2f Vector2f::operator+(const Vector2f vec) {
    return Vector2f(x + vec.x, y + vec.y);
}

Vector2f Vector2f::operator-(const Vector2f vec) {
    return Vector2f(x - vec.x, y - vec.y);
}

Vector2f Vector2f::operator*(float f) {
    return Vector2f(x * f, y * f);
}

Vector2f Vector2f::operator/(float f) {
    return Vector2f(x / f, y / f);
}

Vector2f& Vector2f::operator=(const Vector2f vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}

bool Vector2f::operator==(const Vector2f vec) {
    if (x == vec.x && y == vec.y) {
        return true;
    } else {
        return false;
    }
}

Vector2f& Vector2f::operator+=(const Vector2f& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2f& Vector2f::operator*=(float f) {
    x *= f;
    y *= f;
    return *this;
}

Vector2f& Vector2f::operator/=(float f) {
    x /= f;
    y /= f;
    return *this;
}

float Vector2f::length() {
    if (x == 0 && y == 0) {
        return 0;
    }
    return sqrt(pow(x, 2) + pow(y, 2));
}
