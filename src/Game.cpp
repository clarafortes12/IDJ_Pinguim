#include "Game.h"
#include "Resources.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height){
    if(instance == nullptr){
        instance = this;
        int init_SDL = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
        
        if(init_SDL != 0){
            cout << "Erro de inicialização do SDL" << endl;
            cout << SDL_GetError() << endl;
        }
        
        int init_IMG = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

        if(init_IMG == 0){
            cout << "Erro de inicialização do IMG" << endl;
            cout << SDL_GetError() << endl;
        }

        int Init_Mix = Mix_Init(MIX_INIT_OGG);

        if(Init_Mix == 0){
            cout << "Erro de inicialização do MIX" << endl;
            cout << SDL_GetError() << endl;
        }

        int mixOpenAudio =  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE);
        
        if(mixOpenAudio == -1){
            cout << "Erro de Abertura de audio" << endl;
            cout << SDL_GetError() << endl;
        }
        
        Mix_AllocateChannels(NUM_CHANNELS);

        this->window =  SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

        if(this->window == nullptr){
            cout << "Erro de criação de Janela" << endl;
            cout << SDL_GetError() << endl;
        }
        
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

        if(this->renderer == nullptr){
            cout << "Erro de renderização" << endl;
            cout << SDL_GetError() << endl;
        }
        
        this->state = new State();
        
        if(state == nullptr){
            cout << "Erro de instanciamento de state" << endl;
        }

    } else{
        cout << "Erro no instanciamento do Game - Ja instanciado" << endl;
    }
}

Game::~Game(){
    delete state;

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();
    SDL_Quit();

    delete instance;
}

void Game::Run(){
    while (!state->QuitRequested()){
        state->Update(0.1f);
        state->Render();

        SDL_RenderPresent(this->renderer);

        SDL_Delay(TIME_DELAY);
    }
    
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
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