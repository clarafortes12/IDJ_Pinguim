#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2{
    public:
        float x, y;
        Vec2();
        Vec2(float x, float y);
        
        float Magnitude();
        float Distance(const Vec2& v);
        float InclinationX();
        float InclinationReta(const Vec2& vec);

        Vec2 GetRotated(float d);
        Vec2 GetNormalized();

        Vec2& operator+=(const Vec2& vec);
        Vec2& operator-=(const Vec2& vec);
        Vec2& operator*=(const Vec2& vec);
        Vec2& operator*=(const float& f);
        Vec2& operator=(const Vec2& vec);

        Vec2 operator+(const Vec2 & vec);
        Vec2 operator-(const Vec2 & vec);
        Vec2 operator*(const Vec2 & vec);
        Vec2 operator*(const float & f) const;
};

#endif
