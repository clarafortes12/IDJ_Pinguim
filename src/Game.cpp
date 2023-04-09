#include "Game.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

Game* Game::instance = 0;

Game::Game(const char* title, int width, int height){
    if(instance != nullptr){
        instance = this;
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
        IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

        int mixInit = Mix_Init(MIX_INIT_OGG);
        int mixOpenAudio =  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE);
        int mixAllocateChannels = Mix_AllocateChannels(NUM_CHANNELS);

        this->window =  SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

        this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }
}

Game::~Game(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();
    SDL_Quit();

    delete instance;

}

void Game::Run(){
    while (state->QuitRequested()){
        state->Update(0/*Mudar*/);
        state->Render();

        SDL_RenderPresent(this->renderer);

        SDL_Delay(TIME_DELAY);
    }
}

SDL_Renderer* Game::GetRenderer(){
    return this->renderer;
}

State& Game::GetState(){
    return *state;
}

Game& Game::GetInstance(){
    if(instance != nullptr){
        return *instance;
    }else{
        instance = new Game(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
        return *instance;
    }
}