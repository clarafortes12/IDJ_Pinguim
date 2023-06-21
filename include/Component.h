#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string.h>
#include <iostream.h>

using namespace std;

#define PI 3.14159265358979323846

class GameObject;

class Component{
    protected:
        GameObject& associated;
    public:
        Component(GameObject& associated);
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(string type) = 0;
        virtual void Start();
        virtual void NotifyCollision(GameObject& other);
};

#endif