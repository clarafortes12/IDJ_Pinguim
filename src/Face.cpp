#include "Face.h"

Face::Face(GameObject& associated) : Component(associated){
    this->hitpoints = 30; //HP
}

void Face::Damage(int damage){
    this->hitpoints -= damage;
    if(hitpoints <= 0){
        associated.RequestDelete();
        
        Sound* sound = (Sound*)associated.GetComponent("Sound");
        
        if(sound != nullptr){
            sound->Play();
        }
    }
}

void Face::Update(float dt){}
void Face::Render(){}

bool Face::Is(string type){
    if(type == "Face"){
        return true;
    } else{
        return false;
    }
}