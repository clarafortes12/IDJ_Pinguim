#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string.h>
#include <iostream.h>
#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

using namespace std;

class Sprite : public Component{
    private:
        shared_ptr<SDL_Texture> texture;
        int width;
        int height;
        SDL_Rect clipRect;
        Vec2 scale;
        Timer selfDestructCount;  

        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;
        bool continuos;
        float secondsToSelfDestruct;     
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, string file, int frameCount=1, float frameTime = 1, bool continuos = true, float secondsToSelfDestruct = 0);
        ~Sprite();
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Render(int x, int y);
        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
};

#endif