#pragma once

class Color {
public:
    Color(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);

    float r;
    float g;
    float b;
    float a;

    Color& operator=(const Color& c);
    bool operator==(const Color& c);
};

