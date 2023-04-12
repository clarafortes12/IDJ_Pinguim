#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <SDL2/SDL_mixer.h>

#include <string.h>
#include <iostream.h>

using namespace std;

class Music{
    private:
        Mix_Music* music;
    public:
        Music();
        Music(string file);
        ~Music();
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();
};

#endif