#include "State.h"

#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"

#include <math.h>

State::State() : music(Music("assets/audio/stageState.ogg")){
	GameObject* go = new GameObject();
	Sprite* bg = new Sprite(*go, "assets/img/ocean.jpg");
	CameraFollower* camera = new CameraFollower(*go);

	go->box = Rect(0, 0, bg->GetWidth(), bg->GetHeight());
	go->AddComponent(bg);

	go->AddComponent(camera);
	
	objectArray.emplace_back(go);

	GameObject* goMap = new GameObject();
	tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    tileMap = new TileMap(*goMap, "assets/map/tileMap.txt", tileSet);
	
	tileMap->SetParallax(1, Vec2(0.5, 0.5));
    
	goMap->box = Rect(0, 0, tileSet->GetTileWidth(), tileSet->GetTileHeight());
	goMap->AddComponent(tileMap);
	
	objectArray.emplace_back(goMap);

	GameObject* alienGo = new GameObject();
    Alien* alien = new Alien(*alienGo, 3);
    
	alienGo->AddComponent(alien);
    alienGo->box = alienGo->box.GetCentered(512, 300);
    
	objectArray.emplace_back(alienGo);

	GameObject* penguinGo = new GameObject();
    PenguinBody* penguin = new PenguinBody(*penguinGo);

    penguinGo->AddComponent(penguin);
    penguinGo->box = penguinGo->box.GetCentered(704, 640);
    
	objectArray.emplace_back(penguinGo);
    
    Camera::Follow(penguinGo);

    music.Open("assets/audio/stageState.ogg");

	this->quitRequested = false;
	this->started = false;
}

State::~State(){
	delete tileSet;
    objectArray.clear();
}

bool State::QuitRequested(){
    return SDL_QuitRequested();
}

void State::LoadAssets(){}

void State::Update(float dt){
	InputManager& instance = InputManager::GetInstance();
	
	if(instance.QuitRequested() || instance.KeyPress(ESCAPE_KEY)){
		this-> quitRequested = true;
	}

	Camera::Update(dt);
	
	int tam = objectArray.size();
	
	for(int i = (tam-1); i >= 0; i--){
        objectArray[i]->Update(dt);

		if(objectArray[i]->IsDead()){
			objectArray.erase(objectArray.begin()+i);
		}
    }

	tam = objectArray.size();
	
	for (int i = 0; i < tam; i++) {
        for (int j = i+1; j < tam; j++) {
            shared_ptr<GameObject> Object1GO = objectArray[i];
            shared_ptr<GameObject> Object2GO = objectArray[j];

            Collider* collider1 = (Collider*)Object1GO->GetComponent("Collider");
            Collider* collider2 = (Collider*)Object2GO->GetComponent("Collider");
            
            if (nullptr != collider1 && nullptr != collider2) {
				float radCollider1 = (Object1GO->angleDeg*PI)/180;
				float radCollider2 = (Object2GO->angleDeg*PI)/180;
				
				if (Collision::IsColliding(collider1->box, collider2->box, radCollider1, radCollider2)) {
					Object1GO->NotifyCollision(*Object2GO);
					Object2GO->NotifyCollision(*Object1GO);
				}
			}
        }
    }

}

void State::Render(){
	int tam = objectArray.size();
	for(int i = 0; i < tam; i++){
        objectArray[i]->Render();
    }
}

void State::Start(){
	LoadAssets();
	
	int tam = objectArray.size();
	for(int i = 0; i < tam; i++){
        objectArray[i]->Start();
    }
	
	this->started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject* go){
	shared_ptr<GameObject> goSharedPtr(go);
	objectArray.push_back(goSharedPtr);
	
	if(started){
		goSharedPtr->Start();
	}
	return weak_ptr<GameObject>(goSharedPtr);
}

weak_ptr<GameObject> State::GetObject(GameObject* go){
	int tam = this->objectArray.size();
    for(int i = 0; i < tam; i++){
        if(go == objectArray[i].get()){
            return weak_ptr<GameObject>(objectArray[i]);
        }
    }
	return weak_ptr<GameObject>();
}