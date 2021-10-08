#pragma once

struct Vec3 : public D3DXVECTOR3
{
private:
    using Base = D3DXVECTOR3;

public:
    Vec3() { x = y = z = 0; };
    Vec3(CONST FLOAT* pf);
    Vec3(const D3DXVECTOR2& v);
    Vec3(const D3DXVECTOR3& v);
    Vec3(const D3DXVECTOR4& v);
    Vec3(CONST D3DXFLOAT16* pf);
    Vec3(const FLOAT& x, const FLOAT& y, const FLOAT& z);

public:
    operator FLOAT* ();
    operator CONST FLOAT* () const;

    Vec3& operator += (CONST Vec3& v);
    Vec3& operator -= (CONST Vec3& v);
    Vec3& operator *= (const FLOAT& s);
    Vec3& operator /= (const FLOAT& s);

    Vec3 operator + () const; // +v
    Vec3 operator - () const; // -v

    Vec3 operator + (CONST Vec3& v) const;
    Vec3 operator - (CONST Vec3& v) const;
    Vec3 operator * (const FLOAT& s) const;
    Vec3 operator / (const FLOAT& s) const;

    friend Vec3 operator * (const FLOAT& s, CONST struct Vec3& v);

    BOOL operator == (CONST Vec3& v) const;
    BOOL operator != (CONST Vec3& v) const;

public:
    operator D3DXVECTOR2() const;
    operator D3DXVECTOR3() const;
    operator D3DXVECTOR4() const;

public:
    float sqrMagnitude() const;
    float magnitude() const;
    Vec3 normalized() const;
    void Normalize();

public:
    static Vec3 Scale(const Vec3& a, const Vec3& b);
    static float Dot(const Vec3& a, const Vec3& b);
    static Vec3 Cross(const Vec3& a, const Vec3& b);
    static Vec3 Lerp(const Vec3& a, const Vec3& b, const float& t);
    static Vec3 ProjectOnVec3(const Vec3& a, const Vec3& vec3); // Project a vector to b vector
    static Vec3 ProjectOnPlane(const Vec3& a, const Vec3& n); // Project a vector to normal vector of plane
    static float Cos(const Vec3& from, const Vec3& to);
    static float Radian(const Vec3& from, const Vec3& to);
    static float Angle(const Vec3& from, const Vec3& to);
    static float Distance(const Vec3& a, const Vec3& b);

public:
    static Vec3 back();
    static Vec3 down();
    static Vec3 forawrd();
    static Vec3 left();
    static Vec3 right();
    static Vec3 up();
    static Vec3 one();
    static Vec3 zero();
};