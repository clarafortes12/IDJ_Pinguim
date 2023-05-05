#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file): tileSet(go, file){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    if(tileSet.IsOpen()){
        this->columns = tileSet.GetWidth()/this->tileWidth;
        this->rows = tileSet.GetHeight()/this->tileHeight;
    }
}

void TileSet::RenderTile(unsigned int index, float x, float y){
    if(index < (unsigned)((columns*rows))){

        int setClipX = (index % columns) * tileWidth;
        int setClipY = (index / columns) * tileHeight; 

        tileSet.SetClip(setClipX, setClipY, this->tileWidth, this->tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}
