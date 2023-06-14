#include "TileMap.h"
#include "Camera.h"
#include "Vec2.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated){
    this->tileSet = tileSet;
    Load(file);
}

void TileMap::Load(string file){
    ifstream openFile(file);

    if( openFile.is_open() ){
        string line;
        
        getline(openFile, line);

        stringstream lineObj(line);
        string valor;
        
        int cont = 0;

        while (getline(lineObj, valor, ',')) { 
            if(cont == 0){
                this->mapWidth = stoi(valor);  
            } else if(cont == 1){
                this->mapHeight = stoi(valor);  
            } else if(cont == 2){
                this->mapDepth = stoi(valor);  
            }
            cont++;
        }

        getline(openFile, line);

        while(!openFile.eof()){
            if(line.size() != 0){
                stringstream lineObj(line);
                string valor;

                while (getline(lineObj, valor, ',')) { 
                    tileMatrix.push_back(stoi(valor) - 1);
                }
            }
            getline(openFile, line);
        } 
        openFile.close();
    }
    
    for (int i = 0; i < mapDepth; i++) {
        parallax.push_back(Vec2());
    }
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    int index = x;
    index += mapWidth * y;
    index += mapWidth * mapHeight * z;

    return tileMatrix[index];
}

void TileMap::Update(float dt){}

void TileMap::Render(){
    int i = 0;
    while(i < mapDepth){
        RenderLayer(i, associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y);
        i++;
    }   
}

bool TileMap::Is(string type){
    if(type == "TileMap"){
        return true;
    } else{
        return false;
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            int tileX = (j * tileSet->GetTileWidth()) - cameraX - (cameraX * parallax[layer].x);
            int tileY = (i * tileSet->GetTileHeight()) - cameraY - (cameraY * parallax[layer].y);
            tileSet->RenderTile((unsigned)At(j, i, layer), tileX, tileY);
        }
    }
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

void TileMap::SetParallax(int layer, Vec2 factor){
    if(layer >= 0 && layer < mapDepth){
        parallax[layer] = factor;
    } else{
        cout<<"Valor inválido de layer"<<endl;
    }
}