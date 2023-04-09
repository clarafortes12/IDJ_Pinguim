#include "State.h"

State::State(){
    this->quitRequested = false;
    char* file = "../recursos/img/ocean.jpg";
    this->bg = Sprite(file);
    
}

bool State::QuitRequested(){
    return SDL_QuitRequested();
}

void State::LoadAssets(){

}

void State::Update(float dt){
    if(QuitRequested() == true){
        this->quitRequested = true;    
    }

}

void State::Render(){
    this->bg.Render(0,0/*Mudar*/);
}
