#include "State.h"

State::State(){
	this->quitRequested = false;
	this->popRequested = false;
	this->started = false;
}

State::~State(){
	this->objectArray.clear();
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


bool State::PopRequested(){
	return this->popRequested;
}

bool State::QuitRequested(){
	return this->quitRequested;
}

void State::StartArray(){
    int tam = objectArray.size();
	for(int i = 0; i < tam; i++){
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt){
    int tam = objectArray.size();
	for(int i = 0; i < tam; i++){
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray(){
    int tam = objectArray.size();
	for(int i = 0; i < tam; i++){
        objectArray[i]->Render();
    }
}