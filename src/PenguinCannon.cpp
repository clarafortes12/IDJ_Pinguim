#include "PenguinCannon.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "State.h"
#include "Bullet.h"
#include "Collider.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody): Component(associated){
    Sprite* sprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->angle = 0;
    this->pBody = penguinBody;
}
    

PenguinCannon::~PenguinCannon(){}

void PenguinCannon::Update(float dt){
    timer.Update(dt);

    shared_ptr<GameObject> penguinBodyPTR = pBody.lock();
    if (!penguinBodyPTR || penguinBodyPTR->IsDead()) {
        associated.RequestDelete();
        return;
    }

    InputManager& inputManager = InputManager::GetInstance();

    Vec2 bodyCenter = penguinBodyPTR->box.GetCentered();

    associated.box = associated.box.GetCentered(bodyCenter.x, bodyCenter.y);

    Vec2 mousePos = Vec2(inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y);

    angle = (mousePos - bodyCenter).InclinationX();
    associated.angleDeg = (angle*180)/PI;

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        Shoot();
    }
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(string type){
    if(type == "PenguinCannon"){
        return true;
    } else{
        return false;
    }
}

void PenguinCannon::Shoot(){
    if(timer.Get() >= COOLDOW_PENGUIN_CANNON){
        timer.Restart();

        Game& game = Game::GetInstance();
        State& state = game.GetState();

        GameObject* bulletGO = new GameObject();
        Bullet* bullet = new Bullet(*bulletGO, angle, 300, 10, 350, "assets/img/penguinbullet.png", 4, 0.375, false, false);

        Vec2 initialPosition = associated.box.GetCentered() + Vec2(50, 0).GetRotated(angle);
        bulletGO->box = bulletGO->box.GetCentered(initialPosition.x, initialPosition.y);
        bulletGO->AddComponent(bullet);
        
        state.AddObject(bulletGO);
    }
}
