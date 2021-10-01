#pragma once

struct Vec4 : public D3DXVECTOR4
{
private:
    using Base = D3DXVECTOR4;

public:
    Vec4() {};
    Vec4(CONST FLOAT* pf);
    Vec4(const D3DXVECTOR2& v);
    Vec4(const D3DXVECTOR3& v);
    Vec4(const D3DXVECTOR4& v);
    Vec4(CONST D3DXFLOAT16* pf);
    Vec4(const FLOAT& x, const FLOAT& y, const FLOAT& z, const FLOAT& w);

public:
    operator FLOAT* ();
    operator CONST FLOAT* () const;

    Vec4& operator += (CONST Vec4& v);
    Vec4& operator -= (CONST Vec4& v);
    Vec4& operator *= (const FLOAT& s);
    Vec4& operator /= (const FLOAT& s);

    Vec4 operator + () const; // -v
    Vec4 operator - () const; // +v

    Vec4 operator + (CONST Vec4& v) const;
    Vec4 operator - (CONST Vec4& v) const;
    Vec4 operator * (const FLOAT& s) const;
    Vec4 operator / (const FLOAT& s) const;

    friend Vec4 operator * (const FLOAT& s, CONST struct Vec4& v);

    BOOL operator == (CONST Vec4& v) const;
    BOOL operator != (CONST Vec4& v) const;

public:
    operator D3DXVECTOR2() const;
    operator D3DXVECTOR3() const;
    operator D3DXVECTOR4() const;

public:
    float sqrMagnitude() const;
    float magnitude() const;
    Vec4 normalized() const;
    void Normalize();

public:
    static Vec4 Scale(const Vec4& a, const Vec4& b);
    static float Dot(const Vec4& a, const Vec4& b);
    static Vec4 Cross(const Vec4& a, const Vec4& b);
    static Vec4 Lerp(const Vec4& a, const Vec4& b, const float& t);
    static Vec4 ProjectOnVec4(const Vec4& a, const Vec4& b); // Project a vector to b vector
    static Vec4 ProjectOnPlane(const Vec4& a, const Vec4& n); // Project a vector to normal vector of plane
    static float Cos(const Vec4& from, const Vec4& to);
    static float Radian(const Vec4& from, const Vec4& to);
    static float Angle(const Vec4& from, const Vec4& to);
    static float Distance(const Vec4& a, const Vec4& b);

public:
    static Vec4 back();
    static Vec4 down();
    static Vec4 forawrd();
    static Vec4 left();
    static Vec4 right();
    static Vec4 up();
    static Vec4 one();
    static Vec4 zero();
};