#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string.h>
#include <iostream.h>

#include "Component.h"
#include "GameObject.h"

using namespace std;

class Sprite : public Component{
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;         
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, string file);
        ~Sprite();
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Render(int x, int y);

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};



#endif