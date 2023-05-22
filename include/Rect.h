#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

#include "Vec2.h"

class Rect {
    public:
        float x, y, w, h;
        Rect();
        Rect(float x, float y, float w, float h);
        
        bool Contains(const Vec2& point);
        float Distance(Rect& rect);

        Vec2 GetCentered();
        Rect GetCentered(float x, float y);

        Rect& operator+=(const Vec2& vec);
        Rect& operator=(const Rect& rect);

        Rect operator+(const Vec2& vec);
        
};
#endif