#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "Face.h"
#include "Vec2.h"
#include "TileSet.h"
#include "TileMap.h"

#include <string.h>
#include <iostream.h>
#include <vector.h>
#include <memory.h>

using namespace std;

#define PI 3.14159265358979323846

class State {

    private:
        //Sprite bg;
        Music music;
        TileSet* tileSet;
        bool quitRequested;
        vector<unique_ptr<GameObject>> objectArray;
        //void Input();
        void AddObject(int mouseX, int mouseY);
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif