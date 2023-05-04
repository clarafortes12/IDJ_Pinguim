#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED

#include "Sprite.h"
#include "GameObject.h"

#include <string.h>
#include <iostream.h>

using namespace std;

class TileSet{
    private:
        Sprite tileSet;
        GameObject go;
        int rows, columns, tileWidth, tileHeight;
    public:
        TileSet(int tileWidth, int tileHeight, string file);
        void RenderTile(unsigned int index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
};

#endif