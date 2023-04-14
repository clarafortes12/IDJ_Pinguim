#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2{
    public:
        float x, y;
        Vec2();
        Vec2(float x, float y);
        Vec2 GetRotated(float d);

        Vec2& operator+=(const Vec2& vec);
        Vec2& operator-=(const Vec2& vec);
        Vec2& operator*=(const float& vec);
        Vec2& operator=(const Vec2& vec);

        friend Vec2 operator+(Vec2 vec0, const Vec2& vec) {
            vec0 += vec;
            return vec0;
        }

        friend Vec2 operator-(Vec2 vec0, const Vec2& vec) {
            vec0 -= vec;
            return vec0;
        }
        
        friend Vec2 operator*(Vec2 vec0, const float& vec) {
            vec0 *= vec;
            return vec0;
        }

        friend Vec2 operator*(const float& f, Vec2 vec) {
            vec *= f;
            return vec;
        }
};

#endif
