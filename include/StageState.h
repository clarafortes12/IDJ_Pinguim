#ifndef STAGE_STATE_H_INCLUDED
#define STAGE_STATE_H_INCLUDED

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "Vec2.h"
#include "TileSet.h"
#include "TileMap.h"

#include <string.h>
#include <iostream.h>
#include <vector.h>
#include <memory.h>

using namespace std;

class StageState : public State{
    private:
        Music music;
        TileSet* tileSet;
        TileMap* tileMap;
    public:
        StageState();
        ~StageState();

        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;

        void Start() override;
        void Pause() override;
        void Resume() override;
};

#endif