#include "Color.h"

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {

}

Color& Color::operator=(const Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
    return *this;
}

bool Color::operator==(const Color& c) {
    if (r == c.r && b == c.b && g == c.g && a == c.a) {
        return true;
    }

    return false;
}
