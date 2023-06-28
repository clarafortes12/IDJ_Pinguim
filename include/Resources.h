#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream.h>
#include <string.h>
#include <unordered_map>
#include <memory>

#include "Game.h"

using namespace std;

class Resources{
    private:
        static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
        static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
        static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
        static unordered_map<string, shared_ptr<TTF_Font>> fontTable;

    public:
        static shared_ptr<SDL_Texture> GetImage(string file);
        static void ClearImages();
        static shared_ptr<Mix_Music> GetMusic(string file);
        static void ClearMusics();
        static shared_ptr<Mix_Chunk> GetSound(string file);
        static void ClearSounds();
        static shared_ptr<TTF_Font> GetFont(string file,int fontSize);
        static void ClearFont();
};


#endif