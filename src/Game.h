#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>

#include "State.h"

#define SCREEN_WIDTH 1024 
#define SCREEN_HEIGHT 600
#define TITLE "Maria Clara 190017503"

#define CHUNKSIZE 1024
#define NUM_CHANNELS 32
#define TIME_DELAY 33

class Game{

    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        Game(const char* title, int width, int height);
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif

