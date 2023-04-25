#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated){
    this->chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Sound(associated){
    Open(file);
}

Sound::~Sound(){
    if(this->chunk != nullptr){
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times){
    int playChannel = Mix_PlayChannel(-1, chunk, times - 1);

    if(playChannel == -1){
        cout << "Erro de Play Channel - Sound" << endl;
        cout << SDL_GetError() << endl;
    } else{
        Mix_Volume(playChannel, MIX_MAX_VOLUME);
        this->channel = playChannel;
    }
}

void Sound::Stop(){
    if(this->chunk != nullptr){
        Mix_HaltChannel(this->channel);
    }
}

void Sound::Open(string file){
    this-> chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr){
        cout << "Erro de LoadWAV - Sound" << endl;
        cout << SDL_GetError() << endl;
    }
}

bool Sound::IsOpen(){
    if(this->chunk != nullptr){
        return true;
    } else{
        return false;
    }
}

void Sound::Update(float dt){}
void Sound::Render(){}

bool Sound::Is(string type){
    if(type == "Sound"){
        return true;
    } else{
        return false;
    }
}