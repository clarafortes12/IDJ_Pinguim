#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <string.h>

using namespace std;

class Bullet : public Component{
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite);
        
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

        int GetDamage();
};

#endif