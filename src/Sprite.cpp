#include "Sprite.h"
#include "Game.h"

static Game& game = Game::GetInstance();

Sprite::Sprite(){
    this->texture = nullptr;
}

Sprite::Sprite(char* file){
    this->texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    if(this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
    }

}

void Sprite::Open(char* file){
    if(this->texture != nullptr){
        Sprite::~Sprite();
    } 

    texture = IMG_LoadTexture(game.GetRenderer(), file);
    
    if(texture == nullptr){
        SDL_GetError();
    }
    
    int queryTexture = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

    SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h){
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(int x, int y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = this->width;
    rect.h = this->height;
    int renderCopy = SDL_RenderCopy(game.GetRenderer(), this->texture, &rect, &rect);
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