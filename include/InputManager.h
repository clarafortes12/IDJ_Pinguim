#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

using namespace std;

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define SPACE_KEY           SDLK_SPACE
#define W_KEY               SDLK_w
#define A_KEY               SDLK_a
#define S_KEY               SDLK_s
#define D_KEY               SDLK_d

class InputManager{
    private:
        bool mouseState[6];
        int mouseUpdate[6];
        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;
        bool quitRequested;
        int updateCounter, mouseX, mouseY;
        InputManager();
        ~InputManager();
    public:
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
        static InputManager& GetInstance();
};
#endif
