#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED


#include <SDL2/SDL_mixer.h>

#include <string.h>
#include <iostream.h>

using namespace std;


#include "Component.h"
#include "GameObject.h"

class Sound : public Component{
    private:
        Mix_Chunk* chunk;
        int channel;
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, string file);
        ~Sound();
        void Play(int times = 1);
        void Stop();
        void Open(string file);
        bool IsOpen();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};



#endif