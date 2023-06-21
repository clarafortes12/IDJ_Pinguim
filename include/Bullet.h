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
        bool targetsPlayer;
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool continuos, bool targetsPlayer);
        
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        void NotifyCollision(GameObject& other) override;

        int GetDamage();
};

#endif