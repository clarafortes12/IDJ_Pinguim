#ifndef CAMERAFOLLOWER_H_INCLUDED
#define CAMERAFOLLOWER_H_INCLUDED

#include "GameObject.h"
#include "Component.h"

#include <string.h>
#include <iostream.h>

using namespace std;

class CameraFollower: public Component{
    public:
        CameraFollower(GameObject& go);
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};

#endif