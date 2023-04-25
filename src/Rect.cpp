#include "Rect.h"

Rect::Rect(){
    this-> x = 0.0;
    this-> y = 0.0;
    this-> w = 0.0;
    this-> h = 0.0;
}

Rect::Rect(float x, float y, float w, float h){
    this-> x = x;
    this-> y = y;
    this-> w = w;
    this-> h = h;
}

bool Rect::Contains(const Vec2& point) const {
    if (x > point.x || (x+w) < point.x) {
        return false;
    } else if (y > point.y || (y+h) < point.y) {
        return false;
    }
    return true;
}