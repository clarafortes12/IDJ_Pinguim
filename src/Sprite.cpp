#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

#include <cmath>

Sprite::Sprite(GameObject& associated) : Component(associated){
    this->texture = nullptr;
    this->scale = Vec2(1,1);
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime, bool continuos, float secondsToSelfDestruct) : Sprite(associated){
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->currentFrame = 0;
    this->timeElapsed = 0;
    this->continuos = continuos;
    this->secondsToSelfDestruct = secondsToSelfDestruct;

    Open(file);
    SetClip(currentFrame * (width/frameCount), 0, this->width/frameCount, this->height);
}

Sprite::~Sprite(){}

void Sprite::Open(string file){
    if(this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
    }

    texture = Resources::GetImage(file);

    int queryTexture = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    if(queryTexture < 0){
        cout << "Erro no Query Texture" << endl;
        cout << SDL_GetError() << endl;
    }
    associated.box.w = this->width;
    associated.box.h = this->height;
}

void Sprite::SetClip(int x, int y, int w, int h){
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

int Sprite::GetWidth(){
    return this->width/frameCount;
}

int Sprite::GetHeight(){
    return this->height;
}

bool Sprite::IsOpen(){
    if(this->texture != nullptr){
        return true;
    } else{
        return false;
    }
}

void Sprite::Update(float dt){
    if(secondsToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }
    timeElapsed += dt;

    if(timeElapsed >= frameTime){
        currentFrame += 1;
    }

    if(currentFrame >= frameCount){
        if(continuos){
            currentFrame = 0;
        } else{
            currentFrame = frameTime - 1;
        }
    }
    SetFrame(currentFrame);
}

void Sprite::Render(){
    Render(associated.box.x - Camera::pos.x , associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y) {
    SDL_Rect rect = { x, y, (int) round(scale.x * clipRect.w), (int) round(scale.y * clipRect.h) };
    int renderCopy = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &rect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    
    if(renderCopy < 0){
        cout << "Erro no Query Texture" << endl;
        cout << SDL_GetError() << endl;
    }
}

bool Sprite::Is(string type){
    if(type == "Sprite"){
        return true;
    } else{
        return false;
    }
}

void Sprite::SetScaleX(float scaleX, float scaleY){
    Vec2 center = associated.box.GetCentered();

    if (scaleX != 0) {
        scale.x = scaleX;
        associated.box.w = GetWidth();
    }
    if (scaleY != 0) {
        scale.y = scaleY;
        associated.box.h = GetHeight();
    }

    associated.box = associated.box.GetCentered(center.x, center.y);
}

Vec2 Sprite::GetScale(){
    return Vec2(scale.x, scale.y);
}

void Sprite::SetFrame(int frame){
    currentFrame = frame;
    SetClip(currentFrame * width / frameCount, 0, width / frameCount, height);
}

void Sprite::SetFrameCount(int frameCount){ 
    this->frameCount = frameCount;
    associated.box.w = GetWidth();
    SetFrame(0);
}

void Sprite::SetFrameTime(float frameTime){
    this->frameTime = frameTime;    
}