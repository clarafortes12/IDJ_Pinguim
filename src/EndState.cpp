#include "EndState.h"

#include "GameData.h"
#include "Camera.h"
#include "Sprite.h"
#include "Text.h"
#include "InputManager.h"

EndState::EndState(){
    GameObject* go = new GameObject();
    Sprite* background;
    
    if (GameData::playerVictory) {
        background = new Sprite(*go, "assets/img/win.jpg");
        backgroundMusic.Open("assets/audio/endStateWin.ogg");
    } else {
        background = new Sprite(*go, "assets/img/lose.jpg");
        backgroundMusic.Open("assets/audio/endStateLose.ogg");
    }
    
    go->AddComponent(background);
    objectArray.emplace_back(go);

    GameObject* titleGo1 = new GameObject();
    Text* text1 = new Text(*titleGo1, "assets/font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "PRESSIONE ESC PARA SAIR", { 255, 0, 0, 255 });
    titleGo1->AddComponent(text1);
    titleGo1->box = titleGo1->box.GetCentered(540, 500);
    objectArray.emplace_back(titleGo1);

    GameObject* titleGo2 = new GameObject();
    Text* text2 = new Text(*titleGo2, "assets/font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "PRESSIONE SPACE PARA REINICIAR", { 255, 0, 0, 255 }, true);
    titleGo2->AddComponent(text2);
    titleGo2->box = titleGo2->box.GetCentered(540, 550);
    objectArray.emplace_back(titleGo2);

}

EndState::~EndState(){}

void EndState::LoadAssets(){}

void EndState::Update(float dt){
    if (!quitRequested && !popRequested) {
        
        InputManager& instance = InputManager::GetInstance();

        UpdateArray(dt);

        if (instance.IsKeyDown(ESCAPE_KEY) || instance.QuitRequested()) {
            quitRequested = true;
            return;
        }

        if (instance.IsKeyDown(SPACE_KEY)) {
            popRequested = true;
            return;
        }
    }
}

void EndState::Render(){
    RenderArray();
}

void EndState::Start(){
    backgroundMusic.Play();
    LoadAssets();
    StartArray();
    started = true;
}

void EndState::Pause(){}

void EndState::Resume(){
    Camera::pos = Vec2();
}