#include "Music.h"
#include "Resources.h"

Music::Music(){}

Music::Music(string file){
    Open(file);
    Play();
}

Music::~Music(){}

void Music::Play(int times){
    if(music){
        int playMusic = Mix_PlayMusic(music.get(), times);
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