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

float Vec2::Magnitude(){
    float mag = sqrt((x*x)+(y*y));
    return mag;
}

float Vec2::Distance(const Vec2& vec){
    Vec2 sub = *this - vec;
    return sub.Magnitude();
}

float Vec2::InclinationX(){
    return atan2(y, x);
}

float Vec2::InclinationReta(const Vec2& vec){
    Vec2 sub = *this - vec;
    return atan2(sub.y, sub.x);
}

Vec2 Vec2::GetRotated(float d){
    float xl = x * cos(d) - y * sin(d);
    float yl = y * cos(d) + x * sin(d);
    return Vec2(xl, yl);
}

Vec2 Vec2::GetNormalized(){
    float mag = Magnitude();
    return Vec2( x/mag , y/mag);
}

Vec2& Vec2::operator+=(const Vec2& vec){
    x += vec.x;
    y += vec.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& vec){
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vec2& Vec2::operator*=(const Vec2& vec){
    x *= vec.x;
    y *= vec.y;
    return *this;
}

Vec2& Vec2::operator*=(const float& f){
    x *= f;
    y *= f;
    return *this;
}

Vec2& Vec2::operator=(const Vec2& vec){
    x = vec.x;
    y = vec.y;
    return *this;
}

Vec2 Vec2::operator+(const Vec2 & vec){
    return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(const Vec2 & vec){
    return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator*(const Vec2 & vec){
    return Vec2(x * vec.x, y * vec.y);
}

Vec2 Vec2::operator*(const float & f) const{
    return Vec2(x * f, y * f);
}
