#include "State.h"

#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <math.h>

/*void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent("Face");
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}*/

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
    TileMap* tileMap = new TileMap(*goMap, "assets/map/tileMap.txt", tileSet);
    
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
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( instance.GetMouseX() + Camera::pos.x, instance.GetMouseX() + Camera::pos.y);
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
