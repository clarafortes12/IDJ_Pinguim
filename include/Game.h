#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>

#include <string.h>
#include <iostream.h>
#include <stack>

using namespace std;

#include "State.h"

#define SCREEN_WIDTH 1024 
#define SCREEN_HEIGHT 600
#define TITLE "Maria Clara 190017503"

#define CHUNKSIZE 1024
#define NUM_CHANNELS 32
#define TIME_DELAY 33

class Game{

    private:
        int frameStart;
        float dt;
        
        static Game* instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        stack<unique_ptr<State>> stateStack;

        void CalculateDeltaTime();
    public:
        Game(string title, int width, int height);
        ~Game();

        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();
        
        void Push(State* state);

        void Run();
        float GetDeltaTime();
};

#endif

