#include "Music.h"

Music::Music(){
    this->music = nullptr;
}

Music::Music(string file){
    this->music = nullptr;
    Open(file);
}

Music::~Music(){
    if(this->music != nullptr){
        Mix_FreeMusic(this->music);
    }
}

void Music::Play(int times){
    if(this->music != nullptr){
        int playMusic = Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop){
    int fadeOutMusic = Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){
    this->music = Mix_LoadMUS(file.c_str());
    if(this->music == nullptr){
        SDL_GetError();
    }
}

bool Music::IsOpen(){
    if(this->music != nullptr){
        return true;
    } else{
        return false;
    }
}