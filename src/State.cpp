#include "State.h"

#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <math.h>

void State::AddObject(int mouseX, int mouseY){
	GameObject* go = new GameObject();

	Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
	if(sprite == nullptr){
		cout << "Erro na criação do Sprite" << endl;
		cout << SDL_GetError() << endl;
	}

	go->box = Rect(mouseX, mouseY, sprite->GetWidth(), sprite->GetHeight());

	Sound* sound = new Sound(*go, "assets/audio/boom.wav");
	if(sound == nullptr){
		cout << "Erro na criação do Sound" << endl;
		cout << SDL_GetError() << endl;
	}
	
	Face * face = new Face(*go);
	if(face == nullptr){
		cout << "Erro na criação da Face" << endl;
		cout << SDL_GetError() << endl;
	}

	go->box = go->box.GetCentered(mouseX, mouseY);

	go->AddComponent(sprite);
    go->AddComponent(sound);
    go->AddComponent(face);

	objectArray.emplace_back(go);
}

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
    
	goMap->box = Rect(0, 0, tileSet->GetTileWidth(), tileSet->GetTileHeight());
	goMap->AddComponent(tileMap);
	
	objectArray.emplace_back(goMap);
	
	this->quitRequested = false;
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

    if (instance.KeyPress(SPACE_KEY)) {
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( instance.GetMouseX() + Camera::pos.x, instance.GetMouseY() + +Camera::pos.y);
		AddObject((int)objPos.x, (int)objPos.y);

    }

	Camera::Update(dt);
	
	int tam = objectArray.size();
	
	for(int i = (tam-1); i >= 0; i--){
        objectArray[i]->Update(dt);

		if(objectArray[i]->IsDead()){
			objectArray.erase(objectArray.begin()+i);
		}
    }

}

void State::Render(){
	int tam = objectArray.size();
	for(int i = 0; i < tam; i++){
        objectArray[i]->Render();
    }
}
