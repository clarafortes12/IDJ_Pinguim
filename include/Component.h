#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string.h>
#include <iostream.h>

using namespace std;

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
};

#endif