#include "InputManager.h"

InputManager::InputManager(){
    this->quitRequested = false;
    this->updateCounter = 0;
    this->mouseX = 0;
    this->mouseY = 0;
    for (int i = 0; i < 6; i++){
        mouseState[i]=0;
        mouseUpdate[i]=0;
    }
}

InputManager::~InputManager(){}
    
void InputManager::Update(){
    SDL_Event event;
	updateCounter += 1;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            if(event.type == SDL_MOUSEBUTTONDOWN){
                mouseState[event.button.button] = true;
            } else{
                mouseState[event.button.button] = false;
            }
            mouseUpdate[event.button.button] = updateCounter;
        }
		
        if( (!event.key.repeat) && (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)) {
            if(event.type == SDL_KEYDOWN){
                keyState[event.key.keysym.sym] = true;
            } else{
                keyState[event.key.keysym.sym] = false;
            }
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
	}
}

bool InputManager::KeyPress(int key){
    if(keyState[key] && keyUpdate[key] == updateCounter){
        return true;
    } else{
        return false;
    }
}

bool InputManager::KeyRelease(int key){
    if(!keyState[key] && keyUpdate[key] == updateCounter){
        return true;
    } else{
        return false;
    }
}

bool InputManager::IsKeyDown(int key){
    return keyState[key];
}

bool InputManager::MousePress(int button){
    if(mouseState[button] && mouseUpdate[button] == updateCounter){
        return true;
    } else{
        return false;
    }
}

bool InputManager::MouseRelease(int button){
    if(!mouseState[button] && mouseUpdate[button] == updateCounter){
        return true;
    } else{
        return false;
    }
}

bool InputManager::IsMouseDown(int button){
    return mouseState[button];
}

int InputManager::GetMouseX(){
    return this->mouseX;
}

int InputManager::GetMouseY(){
    return this->mouseY;
}   

bool InputManager::QuitRequested(){
    return this->quitRequested;
}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}