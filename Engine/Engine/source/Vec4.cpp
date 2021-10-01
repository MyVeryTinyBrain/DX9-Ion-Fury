#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Vec4.h"

Vec4::Vec4(const FLOAT* pf) : Base(pf)
{
}

Vec4::Vec4(const D3DXVECTOR2& v) : Base(v.x, v.y, 0, 0)
{
}

Vec4::Vec4(const D3DXVECTOR3& v) : Base(v.x, v.y, v.z, 0)
{
}

Vec4::Vec4(const D3DXVECTOR4& v) : Base(v)
{
}

Vec4::Vec4(const D3DXFLOAT16* pf) : Base(pf)
{
}

Vec4::Vec4(const FLOAT& x, const FLOAT& y, const FLOAT& z, const FLOAT& w) : Base(x, y, z, w)
{
}

Vec4::operator FLOAT* ()
{
	return Base::operator FLOAT * ();
}

Vec4::operator const FLOAT* () const
{
	return Base::operator const FLOAT * ();
}

Vec4& Vec4::operator+=(const Vec4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vec4& Vec4::operator-=(const Vec4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vec4& Vec4::operator*=(const FLOAT& s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vec4& Vec4::operator/=(const FLOAT& s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

Vec4 Vec4::operator+() const
{
	return { +x,+y,+z,+w };
}

Vec4 Vec4::operator-() const
{
	return { -x,-y,-z,-w };
}

Vec4 Vec4::operator+(const Vec4& v) const
{
	return { x + v.x,y + v.y,z + v.z,w + v.w };
}

Vec4 Vec4::operator-(const Vec4& v) const
{
	return { x - v.x,y - v.y,z - v.z, w- v.w };
}

Vec4 Vec4::operator*(const FLOAT& s) const
{
	return { x * s,y * s,z * s, w * s };
}

Vec4 Vec4::operator/(const FLOAT& s) const
{
	return { x / s,y / s,z / s, w/s };
}

Vec4 operator*(const FLOAT& s, const Vec4& v)
{
	return { v.x * s,v.y * s,v.z * s, v.w*s };
}

BOOL Vec4::operator==(const Vec4& v) const
{
	return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
}

BOOL Vec4::operator!=(const Vec4& v) const
{
	return !(*this == v);
}

Vec4::operator D3DXVECTOR2() const
{
	return D3DXVECTOR2(x, y);
}

Vec4::operator D3DXVECTOR3() const
{
	return D3DXVECTOR3(x, y, z);
}

Vec4::operator D3DXVECTOR4() const
{
	return D3DXVECTOR4(x, y, z, w);
}

float Vec4::sqrMagnitude() const
{
	return D3DXVec4LengthSq(this);
}

float Vec4::magnitude() const
{
	return D3DXVec4Length(this);
}

Vec4 Vec4::normalized() const
{
	Vec4 normalizedVec;
	D3DXVec4Normalize(&normalizedVec, this);
	return normalizedVec;
}

void Vec4::Normalize()
{
	D3DXVec4Normalize(this, this);
}

Vec4 Vec4::Scale(const Vec4& a, const Vec4& b)
{
	return Vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

float Vec4::Dot(const Vec4& a, const Vec4& b)
{
	return D3DXVec4Dot(&a, &b);
}

Vec4 Vec4::Cross(const Vec4& a, const Vec4& b)
{
	D3DXVECTOR3 result;
	D3DXVECTOR3 _a = a;
	D3DXVECTOR3 _b = b;
	D3DXVec3Cross(&result, &_a, &_b);
	return result;
}

Vec4 Vec4::Lerp(const Vec4& a, const Vec4& b, const float& t)
{
	Vec4 result;
	D3DXVec4Lerp(&result, &a, &b, t);
	return result;
}

Vec4 Vec4::ProjectOnVec4(const Vec4& a, const Vec4& b)
{
	return Dot(b, a) / Dot(b, b) * b;
}

Vec4 Vec4::ProjectOnPlane(const Vec4& a, const Vec4& n)
{
	return a - ProjectOnVec4(n, a);
}

float Vec4::Cos(const Vec4& from, const Vec4& to)
{
	return Dot(from.normalized(), to.normalized());
}

float Vec4::Radian(const Vec4& from, const Vec4& to)
{
	float demoninator = sqrtf(from.sqrMagnitude() * to.sqrMagnitude());
	if (demoninator < D3DX_16F_EPSILON)
		return 0;

	float dot = Dot(from, to);
	float cos = dot / demoninator;
	return acosf(cos);
}

float Vec4::Angle(const Vec4& from, const Vec4& to)
{
	return Radian(from, to) * 180.0f / D3DX_PI;
}

float Vec4::Distance(const Vec4& a, const Vec4& b)
{
	return (b - a).magnitude();
}

Vec4 Vec4::back()
{
	return Vec4(0, 0, -1, 0);
}

Vec4 Vec4::down()
{
	return Vec4(0, -1, 0, 0);
}

Vec4 Vec4::forawrd()
{
	return Vec4(0, 0, 1, 0);
}

Vec4 Vec4::left()
{
	return Vec4(-1, 0, 0, 0);
}

Vec4 Vec4::right()
{
	return Vec4(1, 0, 0, 0);
}

Vec4 Vec4::up()
{
	return Vec4(0, 1, 0, 0);
}

Vec4 Vec4::one()
{
	return Vec4(1, 1, 1, 0);
}

Vec4 Vec4::zero()
{
	return Vec4(0, 0, 0, 0);
}
