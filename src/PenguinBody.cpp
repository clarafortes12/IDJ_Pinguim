#include "PenguinBody.h"

#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Sound.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"

#include <cmath>

PenguinBody* PenguinBody::player = nullptr;


PenguinBody::PenguinBody(GameObject& associated):Component(associated){
    Sprite* sprite = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(sprite);
    
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->speed = Vec2(0, 0);
    this->linearSpeed = 0;
    this->angle = 0;
    this->hp = 100;

    player = this;
}

PenguinBody::~PenguinBody(){
    player = nullptr;
}

void PenguinBody::Start(){
    Game& game = Game::GetInstance();
    State& state = game.GetCurrentState();

    GameObject* goPenguinCannon = new GameObject();
    
    PenguinCannon* penguinCannon = new PenguinCannon(*goPenguinCannon, state.GetObject(&associated));
    goPenguinCannon->AddComponent(penguinCannon);
    
    this->pCannon = state.AddObject(goPenguinCannon);
}

void PenguinBody::Update(float dt){
    if (hp <= 0) {
        associated.RequestDelete();
        shared_ptr<GameObject> penguinCannonPTR = pCannon.lock();
    
        if (penguinCannonPTR) {
            penguinCannonPTR->RequestDelete();
        }

        Camera::Unfollow();

        GameObject* explosionGO = new GameObject();
        Sprite* explosionSprite = new Sprite(*explosionGO, "assets/img/penguindeath.png", 5, 0.3, false, 1.5);
        Sound* explosionSound = new Sound(*explosionGO, "assets/audio/boom.wav");

        explosionSound->Play();
        
        explosionGO->AddComponent(explosionSound);
        explosionGO->AddComponent(explosionSprite);

        Vec2 explosionCenter = associated.box.GetCentered();
        explosionGO->box = explosionGO->box.GetCentered(explosionCenter.x, explosionCenter.y);
        
        Game::GetInstance().GetCurrentState().AddObject(explosionGO);
        
        return;
    }

    InputManager& inputManager = InputManager::GetInstance();
    linearSpeed = speed.x;

    if (inputManager.IsKeyDown(W_KEY)) {
        linearSpeed = min(linearSpeed + (ACCELERATION * dt), MAX_SPEED);
    }
    if (inputManager.IsKeyDown(S_KEY)) {
        linearSpeed = max(linearSpeed - (ACCELERATION * dt), -MAX_SPEED_BACK);
    }
    if (inputManager.IsKeyDown(A_KEY)) {
        angle -= ANGLE_SPEED * (1 - (abs(linearSpeed) / (2 * MAX_SPEED))) * dt;
    }
    if (inputManager.IsKeyDown(D_KEY)) {
        angle += ANGLE_SPEED * (1 - (abs(linearSpeed) / (2 * MAX_SPEED))) * dt;
    }

    speed = Vec2(linearSpeed, 0);
    Vec2 movement = speed.GetRotated(angle) * dt;
    associated.box.x += movement.x;
    associated.box.y += movement.y;

    Rect mapRect = {0, 0, 1408, 1280};
    if (associated.box.x >= mapRect.w){
        associated.box.x = mapRect.w;
    } else if (associated.box.x < 0){
        associated.box.x = 0;
    }
    if (associated.box.y >= mapRect.h) {
        associated.box.y = mapRect.h;
    } else if (associated.box.y < 0) {
        associated.box.y = 0;
    }

    associated.angleDeg = (angle*180)/PI;
}

void PenguinBody::Render(){}

bool PenguinBody::Is(string type){
    if(type == "PenguinBody"){
        return true;
    } else{
        return false;
    }
}

void PenguinBody::NotifyCollision(GameObject& other){
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if (nullptr != bullet) {
        if (bullet->targetsPlayer) {
            hp -= bullet->GetDamage();
        }
    }
}

Vec2 PenguinBody::GetPosition() {
    return associated.box.GetCentered();
}