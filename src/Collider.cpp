#include "Collider.h"

#ifdef DEBUG

#include "Camera.h"
#include "Game.h"

#include "SDL2/SDL.h"

#endif

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt){
    this->box = associated.box;
    this->box.w *= scale.x;
    this->box.h *= scale.y;
    Vec2 boxCenter = associated.box.GetCentered();
    this->box = box.GetCentered(boxCenter.x, boxCenter.y);

    this->box += offset.GetRotated((associated.angleDeg*PI)/180);
}

void Collider::Render(){
#ifdef DEBUG
    Vec2 center = box.GetCentered();
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg/(180/PI) ) + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg/(180/PI) ) + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};
    
    point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/PI) ) + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};
    
    point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/PI) ) + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}

bool Collider::Is(string type){
    if(type == "Collider"){
        return true;
    } else{
        return false;
    }
}

void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}

void Collider::SetOffSet(Vec2 offset){
    this->offset = offset;
}