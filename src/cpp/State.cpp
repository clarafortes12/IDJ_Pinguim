#include "../header/State.h"

State::State(): bg(Sprite("recursos/img/ocean.jpg")), music(Music("recursos/audio/stageState.ogg")){
    this->quitRequested = false;
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
    this->bg.Render(0, 0);
}
