#include "Minion.h"

#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "Bullet.h"
#include "Collider.h"

#include <cmath>
#include <cstdlib>


Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg): Component(associated), alienCenter(alienCenter){
    Sprite* sprite = new Sprite(associated, "assets/img/minion.png");
    
    float scaleValue = (((float) rand() / RAND_MAX) * 0.5) + 1;
    sprite->SetScaleX(scaleValue,scaleValue);
    
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->arc = arcOffsetDeg;
}

void Minion::Update(float dt){
    shared_ptr<GameObject> alienCenterGO = alienCenter.lock();

    if (!alienCenterGO) {
        associated.RequestDelete();
        return;
    }

    float distance = rotationSpeed * dt;
    arc = fmod(arc + distance, PI * 2);
    Vec2 movement = Vec2(150, 0).GetRotated(arc);
    Vec2 newPos = alienCenterGO->box.GetCentered() + movement;

    associated.box = associated.box.GetCentered(newPos.x,newPos.y);
    associated.angleDeg = (arc*180)/PI;
}

void Minion::Render(){}

bool Minion::Is(string type){
    if(type == "Minion"){
        return true;
    } else{
        return false;
    }
}

void Minion::Shoot(Vec2 target){
    Game& game = Game::GetInstance();
    State& state = game.GetState();

    Vec2 pos = associated.box.GetCentered();
    Vec2 direction = target - pos;

    GameObject* bulletGO = new GameObject();
    Bullet* bullet = new Bullet(*bulletGO, direction.InclinationX(), 300, 10, 350, "assets/img/minionBullet2.png", 3, 0.375, true, true);

    bulletGO->box = bulletGO->box.GetCentered(pos.x,pos.y);
    bulletGO->AddComponent(bullet);

    state.AddObject(bulletGO);
}
