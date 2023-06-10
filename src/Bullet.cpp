#include "Bullet.h"

#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite): Component(associated){
    Sprite* spriteImagem = new Sprite(associated, sprite);
    associated.AddComponent(spriteImagem);
    
    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = Vec2(speed,0).GetRotated(angle);
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