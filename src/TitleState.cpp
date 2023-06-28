#include "TitleState.h"

#include "Sprite.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Text.h"
#include "CameraFollower.h"

TitleState::TitleState(){
    GameObject* go = new GameObject();
    Sprite* title = new Sprite(*go, "assets/img/title.jpg");

    go->AddComponent(title);
    objectArray.emplace_back(go);

    GameObject* titleGo = new GameObject();
    Text* text = new Text(*titleGo, "assets/font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "PRESSIONE SPACE PARA COMECAR", { 255, 0, 0, 255 }, true);
    titleGo->AddComponent(text);
    titleGo->box = titleGo->box.GetCentered(540, 500);
    objectArray.emplace_back(titleGo);
}

TitleState::~TitleState(){}

void TitleState::LoadAssets(){}

void TitleState::Update(float dt){
    if (!quitRequested && !popRequested) {
        
        InputManager& instance = InputManager::GetInstance();

        UpdateArray(dt);

        if (instance.KeyPress(ESCAPE_KEY) || instance.QuitRequested()) {
            quitRequested = true;
            return;
        }

        if (instance.KeyPress(SPACE_KEY)) {
            Game& game = Game::GetInstance();
            StageState* stageState = new StageState();
            game.Push(stageState);
        }
    }
}
void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
    LoadAssets();
    StartArray();
    started = true;
}

void TitleState::Pause(){}

void TitleState::Resume(){
    Camera::pos = Vec2();
}