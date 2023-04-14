#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <iostream.h>
#include <string.h>
#include <vector.h>
#include <memory.h>
#include <algorithm>

using namespace std;

#include "Component.h"
#include "Rect.h"

class GameObject{
    private:
        vector<unique_ptr<Component>> components;
        bool isDead;
    public:
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);
        Rect box;
};

#endif