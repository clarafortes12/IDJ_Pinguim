#include "Music.h"
#include "Resources.h"

Music::Music(){
    this->music = nullptr;
}

Music::Music(string file){
    this->music = nullptr;
    Open(file);
    Play();
}

Music::~Music(){}

void Music::Play(int times){
    if(this->music != nullptr){
        int playMusic = Mix_PlayMusic(music, times);
        if(playMusic == -1){
            cout << "Erro em dar play na musica" << endl;
            cout << SDL_GetError() << endl;
        }
    }
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){
    this->music = Resources::GetMusic(file);
}

bool Music::IsOpen(){
    if(this->music != nullptr){
        return true;
    } else{
        return false;
    }
}