#include "Resources.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;


shared_ptr<SDL_Texture> Resources::GetImage(string file){
    if (imageTable.find(file) != imageTable.end()) {
        return imageTable.find(file)->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if(texture == nullptr){
        cout << SDL_GetError() << endl;
        cout << "erro no Load da Imagem" << endl;
    }

    shared_ptr<SDL_Texture> texturePTR(texture, [=](SDL_Texture* texture) { SDL_DestroyTexture(texture); });

    imageTable.insert(make_pair(file, texturePTR));
    
    return texturePTR;
}

void Resources::ClearImages(){
    for(auto elemento = imageTable.begin(); elemento != imageTable.end();) {
        auto ptr = elemento->second;
        if (ptr.unique()) {
            elemento = imageTable.erase(elemento);
        } else {
            elemento++;
        }
    }
}

shared_ptr<Mix_Music> Resources::GetMusic(string file){
    if (musicTable.find(file) != musicTable.end()) {
        return musicTable.find(file)->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    
    if(music == nullptr){
        cout << "Erro em abrir a musica" << endl;
        cout << SDL_GetError() << endl;
    }

    shared_ptr<Mix_Music> musicPTR(music, [=](Mix_Music* music) { Mix_FreeMusic(music); });
    musicTable.insert(make_pair(file, musicPTR));
    return musicPTR;
}

void Resources::ClearMusics(){
    for(auto elemento = musicTable.begin(); elemento != musicTable.end();) {
        auto ptr = elemento->second;
        if (ptr.unique()) {
            elemento = musicTable.erase(elemento);
        } else {
            elemento++;
        }
    }
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file){
    if (soundTable.find(file) != soundTable.end()) {
        return soundTable.find(file)->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    
    if(chunk == nullptr){
        cout << "Erro de LoadWAV - Sound" << endl;
        cout << SDL_GetError() << endl;
    }

    shared_ptr<Mix_Chunk> chunkPTR(chunk, [=](Mix_Chunk* chunk) { Mix_FreeChunk(chunk); });
    soundTable.insert(make_pair(file, chunkPTR));
    
    return chunkPTR;
}

void Resources::ClearSounds(){
    for(auto elemento = musicTable.begin(); elemento != musicTable.end();) {
        auto ptr = elemento->second;
        if (ptr.unique()) {
            elemento = musicTable.erase(elemento);
        } else {
            elemento++;
        }
    }

}


shared_ptr<TTF_Font> Resources::GetFont(string file, int fontSize){
    string key = file + to_string(fontSize);

    if (fontTable.find(key) != fontTable.end()) {
        return fontTable.find(key)->second;
    }

    TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
    
    if(font == nullptr){
        cout << "Erro de OpenFont - Text" << endl;
        cout << SDL_GetError() << endl;
    }

    shared_ptr<TTF_Font> fontPTR(font, [=](TTF_Font* font) { TTF_CloseFont(font); });
    fontTable.insert(make_pair(key, fontPTR));
    
    return fontPTR;
}

void Resources::ClearFont(){
    for(auto elemento = fontTable.begin(); elemento != fontTable.end();) {
        auto ptr = elemento->second;
        if (ptr.unique()) {
            elemento = fontTable.erase(elemento);
        } else {
            elemento++;
        }
    }
}