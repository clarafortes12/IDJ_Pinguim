#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

#include "Vec2.h"

class Rect {
    public:
        float x, y, w, h;
        Rect();
        Rect(float x, float y, float w, float h);
        bool Contains(const Vec2& point) const;
        //void showReact();
        //Vec2* sumVec(Vec2* vetor1, Vec2* vetor1);
        //Vec2* multiVec(Vec2* vetor, float escalar);
};
#endif