#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Vec2.h"
#include "GameObject.h"

class Camera{
    private:
        static GameObject* focus;
    public:
        static Vec2 pos;
        static Vec2 speed;
        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
};

#endif