#ifndef TITLE_STATE_H_INCLUDED
#define TITLE_STATE_H_INCLUDED

#include "State.h"

class TitleState : public State{
    public:
        TitleState();
        ~TitleState();

        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;

        void Start() override;
        void Pause() override;
        void Resume() override;
};

#endif