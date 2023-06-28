#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#include <string.h>
#include <vector.h>
#include <queue>
#include <memory.h>

using namespace std;

#define COOLDOW_ALIEN 1.0

class Alien : public Component{
    private:
        Vec2 speed;
        int hp;
        int nMinions;
        vector<weak_ptr<GameObject>> minionArray;

        enum AlienState { MOVING, RESTING };
        AlienState state;
        Timer restTimer;
        Vec2 destination;

        float timeOffset;
    public:
        static int alienCount;
        Alien(GameObject& associated, int nMinions, float timeOffset);
        ~Alien();
        
        void Start() override;
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        void NotifyCollision(GameObject& other) override;

        void Shoot();
};

#endif