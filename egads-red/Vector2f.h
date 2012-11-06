#pragma once

class Vector2f {
public:
    Vector2f(float x = 0, float y = 0);
    Vector2f(const Vector2f& c);

    float x;
    float y;

    float length();

    Vector2f operator+(const Vector2f v);
    Vector2f operator-(const Vector2f v);
    Vector2f operator*(float f);
    Vector2f operator/(float f);
    Vector2f& operator=(const Vector2f v);
    bool operator==(const Vector2f v);

    Vector2f& operator+=(const Vector2f& v);
    Vector2f& operator-=(const Vector2f& v);
    Vector2f& operator*=(float f);
    Vector2f& operator/=(float f);
};
