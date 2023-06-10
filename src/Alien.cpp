#include "Alien.h"

#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"

#include <cmath>

Alien::Alien(GameObject& associated, int nMinions): Component(associated){
    Sprite* sprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(sprite);

    this->speed = Vec2(200,0);
    this->nMinions = nMinions;
    this->hp = 30;
}

Alien::~Alien(){
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
    if (this->hp <= 0) {
        associated.RequestDelete();
        return;
    }
    
    associated.angleDeg = fmod(associated.angleDeg + 10 * rotationSpeed * dt, 360);

    InputManager& inputManager = InputManager::GetInstance();

    Vec2 mousePos = Vec2(inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y);

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.emplace(Action::SHOOT, mousePos.x, mousePos.y);
    }
    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.emplace(Action::MOVE, mousePos.x, mousePos.y);
    }

    if(!taskQueue.empty()){
        Action action = taskQueue.front();

        if(action.type == Action::MOVE){
            Vec2 boxPos = associated.box.GetCentered();
            Vec2 actPos = Vec2(action.pos.x, action.pos.y);
            Vec2 direction = actPos - boxPos;
            Vec2 movement = speed.GetRotated(direction.InclinationX()) * dt;

            if (boxPos.Distance(actPos) < movement.Magnitude()) {
                associated.box = associated.box.GetCentered(actPos.x, actPos.y);
                taskQueue.pop();
            } else {
                associated.box.x += movement.x;
                associated.box.y += movement.y;
            }
        } else if(action.type == Action::SHOOT){
            float distanceMin = 1e10; 
            int minionIndex = -1;
            int tam = minionArray.size();
            for (int i = 0; i < tam; i++) {
                shared_ptr<GameObject> minionSharedPtr = minionArray[i].lock();
                if (minionSharedPtr) {
                    float distance = action.pos.Distance(minionSharedPtr->box.GetCentered());
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
                        minion->Shoot(Vec2(action.pos.x,action.pos.y));
                    }
                }
            }
            taskQueue.pop();
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

Alien::Action::Action(ActionType type, float x, float y){
    this->type = type;
    this->pos = Vec2(x, y);
}