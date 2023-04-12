#include "../header/Sprite.h"
#include "../header/Game.h"

Sprite::Sprite(){
    this->texture = nullptr;
}

Sprite::Sprite(string file){
    this->texture = nullptr;
    Open(file);
    SetClip(0, 0, this->width, this->height);
}

Sprite::~Sprite(){
    if(this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
    }

}

void Sprite::Open(string file){
    if(this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
    }

    this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    
    if(texture == nullptr){
        cout << SDL_GetError() << endl;
        cout << "erro no Load da Imagem" << endl;
    }
    
    int queryTexture = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    if(queryTexture < 0){
        cout << "Erro no Query Texture" << endl;
        cout << SDL_GetError() << endl;
    }
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
    int renderCopy = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &rect);
    
    if(renderCopy < 0){
        cout << "Erro no Query Texture" << endl;
        cout << SDL_GetError() << endl;
    }
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