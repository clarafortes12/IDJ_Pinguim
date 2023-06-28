#ifndef END_STATE_H_INCLUDED
#define END_STATE_H_INCLUDED

#include "Music.h"
#include "State.h"

class EndState : public State{
    private:
        Music backgroundMusic;
    public:
        EndState();
        ~EndState();

        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;

        void Start() override;
        void Pause() override;
        void Resume() override;
};

#endif