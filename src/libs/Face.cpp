#include "Face.h"

Face::Face(GameObject& associated) : Component(associated){
    this->hitpoints = 30; //HP
}

void Face::Damage(int damage){
    this->hitpoints -= damage;
    if(hitpoints <= 0){
        //RequestDelete do GO que o contém (associated)
        
        //GameObject* go = new GameObject;
        //go->RequestDelete();
        
        //play no componente Sound de seu associated
        
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