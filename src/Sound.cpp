#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated){}

Sound::Sound(GameObject& associated, string file) : Sound(associated){
    Open(file);
}

Sound::~Sound(){}

void Sound::Play(int times){
    int playChannel = Mix_PlayChannel(-1, chunk.get(), times - 1);

    if(playChannel == -1){
        cout << "Erro de Play Channel - Sound" << endl;
        cout << SDL_GetError() << endl;
    } else{
        Mix_Volume(playChannel, MIX_MAX_VOLUME);
        this->channel = playChannel;
    }
}

void Sound::Stop(){
    if(chunk){
        Mix_HaltChannel(this->channel);
    }
}

void Sound::Open(string file){
    this->chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(){
    if(chunk){
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