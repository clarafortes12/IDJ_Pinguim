#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
    this->isDead = false;
}

GameObject::~GameObject(){
    this->components.clear();

}

void GameObject::Update(float dt){
    int tam = this->components.size();
    for(int i = 0; i < tam; i++){
        components[i]->Update(dt);
    }
}

void GameObject::Render(){
    int tam = this->components.size();
    for(int i = 0; i < tam; i++){
        components[i]->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
    int tam = this->components.size();
    for(int i = 0; i < tam; i++){
        if(components[i].get() == cpt){
            components.erase(components.begin()+i);
        }
    }
}

Component* GameObject::GetComponent(string type){
    int tam = this->components.size();
    for(int i = 0; i < tam; i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }
    return nullptr;
}
