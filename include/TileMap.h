#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <iostream.h>
#include <string.h>
#include <vector.h>
#include <fstream>
#include <sstream>  

using namespace std;

#include "TileSet.h"
#include "GameObject.h"
#include "Component.h"

class TileMap : public Component{
    private:
        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth, mapHeight, mapDepth;
    public:
        TileMap(GameObject& associated, string file, TileSet* tileSet);
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();
        
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};


#endif