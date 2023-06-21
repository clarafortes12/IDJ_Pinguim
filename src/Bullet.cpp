#include "Bullet.h"

#include "Sprite.h"
#include "Collider.h"
#include "Alien.h"
#include "PenguinBody.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool continuos,bool targetsPlayer): Component(associated){
    Sprite* spriteImagem = new Sprite(associated, sprite, frameCount, frameTime, continuos);
    associated.AddComponent(spriteImagem);

    
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);
    
    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = Vec2(speed,0).GetRotated(angle);
    this->targetsPlayer = targetsPlayer;
}

void Bullet::Update(float dt){
    Vec2 movement = speed * dt;

    associated.box.x += movement.x;
    associated.box.y += movement.y;

    distanceLeft -= movement.Magnitude();

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}
void Bullet::Render(){}

bool Bullet::Is(string type){
    if(type == "Bullet"){
        return true;
    } else{
        return false;
    }
}

int Bullet::GetDamage(){
    return this->damage;
}

void Bullet::NotifyCollision(GameObject& other){
    Alien* alien = (Alien*)other.GetComponent("Alien");
    PenguinBody* penguinBody = (PenguinBody*)other.GetComponent("PenguinBody");

    if (nullptr != alien && !targetsPlayer) {
        associated.RequestDelete();
    }

    if (nullptr != penguinBody && targetsPlayer) {
        associated.RequestDelete();
    }
}