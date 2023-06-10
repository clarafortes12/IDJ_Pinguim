#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <string.h>
#include <vector.h>
#include <queue>
#include <memory.h>

using namespace std;

class Alien : public Component{
    private:
        class Action{
            public:
                enum ActionType {
                    MOVE,
                    SHOOT,
                };
                ActionType type;
                Vec2 pos;
                Action(ActionType type, float x, float y);
                
        };
        Vec2 speed;
        int hp;
        int nMinions;
        queue<Action> taskQueue;
        vector<weak_ptr<GameObject>> minionArray;
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};

#endif