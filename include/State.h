#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "GameObject.h"

#include <string.h>
#include <iostream.h>
#include <vector.h>
#include <memory.h>

using namespace std;

class State {
    protected:
        bool quitRequested;
        bool popRequested;
        bool started;
        vector<shared_ptr<GameObject>> objectArray;
    public:
        State();
        virtual ~State();

        virtual void LoadAssets() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        
        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        
        virtual weak_ptr<GameObject> AddObject(GameObject* go);
        virtual weak_ptr<GameObject> GetObject(GameObject* go);

        bool PopRequested();
        bool QuitRequested();

        void StartArray();
        virtual void UpdateArray(float dt);
        virtual void RenderArray();
};

#endif