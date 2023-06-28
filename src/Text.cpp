#include "Text.h"

#include "Camera.h"
#include "Game.h"
#include "Resources.h"

Text::Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, bool blink): Component(associated){
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->blink = blink;
    this->display = true;
    this->blinkTimer = new Timer();

    RemakeTexture();
}

Text::~Text(){
    delete blinkTimer;
}


void Text::Update(float dt){
    if(blink) {
        blinkTimer->Update(dt);
        if (blinkTimer->Get() > BLINK_PERIOD) {
            display = !display;
            blinkTimer->Restart();
        }
    }
}

void Text::Render(){
    if(!display) {
        return;
    }
    
    SDL_Rect clipRect = { 0, 0, (int)associated.box.w, (int)associated.box.h };
    SDL_Rect tempRect = { (int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), clipRect.w, clipRect.h };
    
    int renderCopy = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &tempRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (renderCopy != 0) {
        cout<<" Render do Text não realizado de forma correta"<<endl;
        cout<<SDL_GetError()<<endl;
    }
}

bool Text::Is(string type){
    if(type == "Text"){
        return true;
    } else{
        return false;
    }
}

void Text::SetText(string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){
    font = Resources::GetFont(fontFile, fontSize);
    
    SDL_Surface* surface = nullptr;

    switch(style) {
        case (TextStyle::SOLID):
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case (TextStyle::BLENDED):
            surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
        case (TextStyle::SHADED):
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, { 0, 0, 0, 1 });
            break;
    }

    if (!surface ) {
        cout << "Não conseguiu criar a surface de texto"<< endl;
        return;
    }

    associated.box.w = surface->w;
    associated.box.h = surface->h;
    
    SDL_Texture* textureSurface = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

    texture = shared_ptr<SDL_Texture>(textureSurface, [=](SDL_Texture* texture) { SDL_DestroyTexture(texture);});
    
    SDL_FreeSurface(surface);   
}