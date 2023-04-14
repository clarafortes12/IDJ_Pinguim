#include "Vec2.h"

#include <math.h>

Vec2::Vec2(){
    this-> x = 0.0;
    this-> y = 0.0;
}

Vec2::Vec2(float x, float y){
    this-> x = x;
    this-> y = y;
}

Vec2 Vec2::GetRotated(float d) {
    float xl = x * cos(d) - y * sin(d);
    float yl = y * cos(d) + x * sin(d);
    return Vec2(xl, yl);
}

Vec2& Vec2::operator+=(const Vec2& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vec2& Vec2::operator*=(const float& f) {
    x *= f;
    y *= f;
    return *this;
}

Vec2& Vec2::operator=(const Vec2& vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}