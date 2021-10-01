#pragma once

struct Vec2 : public D3DXVECTOR2
{
private:
    using Base = D3DXVECTOR2;

public:
    Vec2();
    Vec2(CONST FLOAT* pf);
    Vec2(const D3DXVECTOR2& v);
    Vec2(const D3DXVECTOR3& v);
    Vec2(const D3DXVECTOR4& v);
    Vec2(CONST D3DXFLOAT16* pf);
    Vec2(const FLOAT& x, const FLOAT& y);
    Vec2(const POINT& pt);

public:
    operator FLOAT* ();
    operator CONST FLOAT* () const;

    Vec2& operator += (CONST Vec2& v);
    Vec2& operator -= (CONST Vec2& v);
    Vec2& operator *= (const FLOAT& s);
    Vec2& operator /= (const FLOAT& s);

    Vec2 operator + () const; // +v
    Vec2 operator - () const; // -v

    Vec2 operator + (CONST Vec2& v) const;
    Vec2 operator - (CONST Vec2& v) const;
    Vec2 operator * (const FLOAT& s) const;
    Vec2 operator / (const FLOAT& s) const;

    friend Vec2 operator * (const FLOAT& s, CONST struct Vec2& v);

    BOOL operator == (CONST Vec2& v) const;
    BOOL operator != (CONST Vec2& v) const;

public:
    operator D3DXVECTOR2() const;
    operator D3DXVECTOR3() const;
    operator D3DXVECTOR4() const;
    operator POINT() const;

public:
    float sqrMagnitude() const;
    float magnitude() const;
    Vec2 normalized() const;
    void Normalize();

public:
    static Vec2 Scale(const Vec2& a, const Vec2& b);
    static float Dot(const Vec2& a, const Vec2& b);
    static D3DXVECTOR3 Cross(const Vec2& a, const Vec2& b);
    static Vec2 Lerp(const Vec2& a, const Vec2& b, const float& t);
    static Vec2 ProjectOnVec2(const Vec2& a, const Vec2& vec2);
    static float Cos(const Vec2& from, const Vec2& to);
    static float Radian(const Vec2& from, const Vec2& to);
    static float Angle(const Vec2& from, const Vec2& to);
    static float Angle180(const Vec2& dir);
    static float Angle360(const Vec2& dir);
    static float Distance(const Vec2& a, const Vec2& b);
    static float SqrDistance(const Vec2& a, const Vec2& b);

public:
    static Vec2 down();
    static Vec2 left();
    static Vec2 right();
    static Vec2 up();
    static Vec2 one();
    static Vec2 zero();
    static Vec2 Direction(const float& angle);
};

