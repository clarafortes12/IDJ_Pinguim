#ifndef PENGUINCANNON_H_INCLUDED
#define PENGUINCANNON_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "PenguinBody.h"
#include "Timer.h"
#include "StageState.h"

#include <string.h>
#include <vector.h>
#include <memory.h>

using namespace std;

#define COOLDOW_PENGUIN_CANNON 0.5

class PenguinCannon: public Component{
    private:
        weak_ptr<GameObject> pBody;
        float angle;
        Timer timer;
    public:
        PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);
        ~PenguinCannon();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        
        void Shoot();
};


#endif