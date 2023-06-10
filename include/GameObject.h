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
        bool started;
    public:
        Rect box;
        double angleDeg;
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);
        void Start();
};

#endif