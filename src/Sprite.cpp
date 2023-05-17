#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
    this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated){
    Open(file);
    SetClip(0, 0, this->width, this->height);
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
    return this->width;
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

void Sprite::Update(float dt){}

void Sprite::Render(){
    Render(associated.box.x - Camera::pos.x , associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y) {
    SDL_Rect rect = { x, y, clipRect.w, clipRect.h };
    int renderCopy = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &rect);
    
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