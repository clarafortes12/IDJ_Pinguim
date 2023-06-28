#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer{
    private:
        float time = 0;
    public:
        Timer();
        void Update(float dt);
        void Restart();
        float Get();
};

#endif