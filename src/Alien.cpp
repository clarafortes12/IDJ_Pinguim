#include "Alien.h"

#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"

#include <cmath>

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions): Component(associated){
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->speed = Vec2(200,0);
    this->nMinions = nMinions;
    this->hp = 30;
    this->state = AlienState::RESTING;

    alienCount += 1;
}

Alien::~Alien(){
    alienCount--;
    minionArray.clear();
}

void Alien::Start() {
    Game& game = Game::GetInstance();
    State& state = game.GetState();

    for (int i = 0; i < nMinions; i++) {
        GameObject* minionGo = new GameObject();

        float arc = PI * 2 * i / nMinions;

        Minion* minion = new Minion(*minionGo, state.GetObject(&associated), arc);
        minionGo->AddComponent(minion);
        
        weak_ptr<GameObject> minionSharedPtr = state.AddObject(minionGo);
        minionArray.push_back(minionSharedPtr);
    }
}

void Alien::Update(float dt){
    if (hp <= 0) {
        associated.RequestDelete();

        GameObject* explosionGO = new GameObject();
        Sprite* explosionSprite = new Sprite(*explosionGO, "assets/img/aliendeath.png", 4, 0.3, false, 1.2);
        Sound* explosionSound = new Sound(*explosionGO, "assets/audio/boom.wav");

        explosionSound->Play();
        
        explosionGO->AddComponent(explosionSound);
        explosionGO->AddComponent(explosionSprite);

        Vec2 alienCenter = associated.box.GetCentered();
        explosionGO->box = explosionGO->box.GetCentered(alienCenter.x, alienCenter.y);
    
        Game::GetInstance().GetState().AddObject(explosionGO);
        return;
    }

    restTimer.Update(dt);
    PenguinBody* player = PenguinBody::player;
    
    associated.angleDeg = fmod(associated.angleDeg + 10 * rotationSpeed * dt, 360);
    Vec2 position = associated.box.GetCentered();

    if (state == AlienState::RESTING && player && restTimer.Get() >= COOLDOW_ALIEN) {
        destination = player->GetPosition();

        float direction = (destination - position).InclinationX();
        speed = Vec2(speed.Magnitude(), 0).GetRotated(direction);
        state = AlienState::MOVING;
    }

    if(state == AlienState::MOVING){

        if (associated.box.GetCentered().Distance(destination) < speed.Magnitude() * dt) {
            associated.box = associated.box.GetCentered(destination.x, destination.y);
            state = AlienState::RESTING;
            restTimer.Restart();

            Shoot();
            
        } else {
            associated.box.x += speed.x * dt;
            associated.box.y += speed.y * dt;
        }
    }
}

void Alien::Render(){}

bool Alien::Is(string type){
    if(type == "Alien"){
        return true;
    } else{
        return false;
    }
}

void Alien::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if (nullptr != bullet) {
        if (!bullet->targetsPlayer) {
            hp -= bullet->GetDamage();
        }
    }
}

void Alien::Shoot(){
    PenguinBody* player = PenguinBody::player;
    
    float distanceMin = 1e10; 
    int minionIndex = -1;

    if (player != nullptr) {

        Vec2 playerPosition = player->GetPosition();

        int tam = minionArray.size();
        for (int i = 0; i < tam; i++) {
            shared_ptr<GameObject> minionSharedPtr = minionArray[i].lock();
            if (minionSharedPtr) {
                float distance = playerPosition.Distance(minionSharedPtr->box.GetCentered());
                if (distance <= distanceMin) {
                    distanceMin = distance;
                    minionIndex = i;
                }
            }
        }

        if (minionIndex != -1) {
            shared_ptr<GameObject> minionGo = minionArray[minionIndex].lock();
            if (minionGo) {
                Minion* minion = (Minion*)minionGo->GetComponent("Minion");
                if (nullptr != minion) {
                    minion->Shoot(Vec2(playerPosition.x,playerPosition.y));
                }
            }
        }
    }
}