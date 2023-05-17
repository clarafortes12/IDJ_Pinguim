#ifndef FACE_H_INCLUDED
#define FACE_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"

#include <string>
#include <math.h>

using namespace std;

class Face : public Component{
    private:
        int hitpoints;
    public:
        Face(GameObject& associated);
        void Damage(int damage);

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};

#endif