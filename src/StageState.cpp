#include "StageState.h"

#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"
#include "Game.h"
#include "TitleState.h"
#include "GameData.h"
#include "EndState.h"

#include <math.h>

StageState::StageState() : State(){
	GameObject* go = new GameObject();
	Sprite* bg = new Sprite(*go, "assets/img/ocean.jpg");
	CameraFollower* camera = new CameraFollower(*go);

	music = Music("assets/audio/stageState.ogg");

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

	Vec2 alienPositions[] = { {0, 0}, {0, 1280}, {1408, 0}, {1408, 1280} };
    float alienOffsets[] = { 0, 1.5, 3.0, 4.5};
    for (int i = 0; i < 4; i++) {
        GameObject* alienGo = new GameObject();
        Alien* alien = new Alien(*alienGo, 4, alienOffsets[i]);
        alienGo->AddComponent(alien);
        alienGo->box = alienGo->box.GetCentered(alienPositions[i].x, alienPositions[i].y);
        objectArray.emplace_back(alienGo);
    }

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

StageState::~StageState(){
	music.Stop(0);
	delete tileSet;
}

void StageState::LoadAssets(){}

void StageState::Update(float dt){
	InputManager& instance = InputManager::GetInstance();
	
	if(!quitRequested && !popRequested){
		
		if (instance.KeyPress(ESCAPE_KEY) ) {
            popRequested = true;
        }
		if (instance.QuitRequested()){
			quitRequested = true;
		}

		Camera::Update(dt);
		
		UpdateArray(dt);

		int tam = objectArray.size();
		
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
		
		for(int i = (tam-1); i >= 0; i--){
			if(objectArray[i]->IsDead()){
				objectArray.erase(objectArray.begin()+i);
			}
		}

		if (PenguinBody::player == nullptr || Alien::alienCount == 0) {
			if(PenguinBody::player != nullptr){
				GameData::playerVictory = true;
			} else{
				GameData::playerVictory = false;
			}
			popRequested = true;

			Game& game = Game::GetInstance();
			EndState* endState = new EndState();
			game.Push(endState);
		}
    }
}

void StageState::Render(){
	RenderArray();
}

void StageState::Start(){
	LoadAssets();
	this->started = true;
	music.Play();
	StartArray();
}

void StageState::Pause(){
	music.Stop(0);
}

void StageState::Resume(){
	music.Play();
}