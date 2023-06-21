#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Rect.h"

#include <string.h>
#include <vector.h>
#include <memory.h>

using namespace std;

class Collider: public Component{
    private:
        Vec2 scale;
        Vec2 offset;
    public:
        Rect box;
        Collider(GameObject& associated, Vec2 scale = Vec2(1,1), Vec2 offset = Vec2());

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

        void SetScale(Vec2 scale);
        void SetOffSet(Vec2 offset);
};

#endif