#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;


SDL_Texture* Resources::GetImage(string file){
    if (imageTable.find(file) != imageTable.end()) {
        return imageTable.find(file)->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if(texture == nullptr){
        cout << SDL_GetError() << endl;
        cout << "erro no Load da Imagem" << endl;
    }

    imageTable.insert(make_pair(file, texture));
    
    return texture;
}

void Resources::ClearImages(){
    for(pair<string, SDL_Texture*> element : imageTable){
        SDL_DestroyTexture(element.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file){
    if (musicTable.find(file) != musicTable.end()) {
        return musicTable.find(file)->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    
    if(music == nullptr){
        cout << "Erro em abrir a musica" << endl;
        cout << SDL_GetError() << endl;
    }
    
    musicTable.insert(make_pair(file, music));
    
    return music;
}

void Resources::ClearMusics(){
    for(pair<string, Mix_Music*> element : musicTable){
        Mix_FreeMusic(element.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file){
    if (soundTable.find(file) != soundTable.end()) {
        return soundTable.find(file)->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    
    if(chunk == nullptr){
        cout << "Erro de LoadWAV - Sound" << endl;
        cout << SDL_GetError() << endl;
    }

    soundTable.insert(make_pair(file, chunk));
    
    return chunk;
}

void Resources::ClearSounds(){
    for(pair<string, Mix_Chunk*> element : soundTable){
        Mix_FreeChunk(element.second);
    }
    soundTable.clear();
}