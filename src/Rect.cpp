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

bool Rect::Contains(const Vec2& point) {
    if (x > point.x || (x+w) < point.x) {
        return false;
    } else if (y > point.y || (y+h) < point.y) {
        return false;
    }
    return true;
}

float Rect::Distance(Rect& rect){
    Vec2 v1 = this->GetCentered();
    Vec2 v2 = rect.GetCentered();
    return v1.Distance(v2);
}

Vec2 Rect::GetCentered(){
    return Vec2(x + w/2, y + h/2);
}

Rect Rect::GetCentered(float x, float y){
    return Rect(x - w/2, y - h/2, w, h);
}

Rect& Rect::operator+=(const Vec2& vec){
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Rect& Rect::operator=(const Rect& rect){
    this->x = rect.x;
    this->y = rect.y;
    this->w = rect.w;
    this->h = rect.h;
    return *this;
}