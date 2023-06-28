#ifndef PENGUINBODY_H_INCLUDED
#define PENGUINBODY_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "StageState.h"

#include <string.h>
#include <vector.h>
#include <memory.h>

using namespace std;

#define MAX_SPEED 300.0
#define MAX_SPEED_BACK 100.0
#define ACCELERATION 50.0
#define ANGLE_SPEED (PI * 2)

class PenguinBody: public Component{
    private:
        weak_ptr<GameObject> pCannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
    public:
        static PenguinBody* player;

        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start() override;
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        void NotifyCollision(GameObject& other) override;
        Vec2 GetPosition();
};

#endif