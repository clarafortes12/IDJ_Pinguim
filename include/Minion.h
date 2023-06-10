#ifndef MINION_H_INCLUDED
#define MINION_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <string.h>
#include <memory.h>

using namespace std;

#define PI 3.14159265358979323846
#define rotationSpeed (PI/2)

class Minion: public Component{
    private:
        weak_ptr<GameObject> alienCenter;
        float arc;
    public:
        Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

        void Shoot(Vec2 target);
};

#endif