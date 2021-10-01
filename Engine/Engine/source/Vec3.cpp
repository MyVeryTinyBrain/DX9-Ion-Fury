#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Vec3.h"

Vec3::Vec3(const FLOAT* pf) : Base(pf)
{
}

Vec3::Vec3(const D3DXVECTOR2& v) : Base(v.x, v.y, 0)
{
}

Vec3::Vec3(const D3DXVECTOR3& v) : Base(v)
{
}

Vec3::Vec3(const D3DXVECTOR4& v) : Base(v.x, v.y, v.z)
{
}

Vec3::Vec3(const D3DXFLOAT16* pf) : Base(pf)
{
}

Vec3::Vec3(const FLOAT& x, const FLOAT& y, const FLOAT& z) : Base(x, y, z)
{
}

Vec3::operator FLOAT* ()
{
	return Base::operator FLOAT * ();
}

Vec3::operator const FLOAT* () const
{
	return Base::operator const FLOAT * ();
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3& Vec3::operator*=(const FLOAT& s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vec3& Vec3::operator/=(const FLOAT& s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vec3 Vec3::operator+() const
{
	return { +x,+y,+z };
}

Vec3 Vec3::operator-() const
{
	return { -x,-y,-z };
}

Vec3 Vec3::operator+(const Vec3& v) const
{
	return { x + v.x,y + v.y,z + v.z };
}

Vec3 Vec3::operator-(const Vec3& v) const
{
	return { x - v.x,y - v.y,z - v.z };
}

Vec3 Vec3::operator*(const FLOAT& s) const
{
	return { x * s,y * s,z * s };
}

Vec3 Vec3::operator/(const FLOAT& s) const
{
	return { x / s,y / s,z / s };
}

Vec3 operator*(const FLOAT& s, const Vec3& v)
{
	return { v.x * s,v.y * s,v.z * s };
}

BOOL Vec3::operator==(const Vec3& v) const
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

BOOL Vec3::operator!=(const Vec3& v) const
{
	return !(*this == v);
}

Vec3::operator D3DXVECTOR2() const
{
	return D3DXVECTOR2(x, y);
}

Vec3::operator D3DXVECTOR3() const
{
	return D3DXVECTOR3(x, y, z);
}

Vec3::operator D3DXVECTOR4() const
{
	return D3DXVECTOR4(x, y, z, 0);
}

float Vec3::sqrMagnitude() const
{
	return D3DXVec3LengthSq(this);
}

float Vec3::magnitude() const
{
	return D3DXVec3Length(this);
}

Vec3 Vec3::normalized() const
{
	Vec3 normalizedVec;
	D3DXVec3Normalize(&normalizedVec, this);
	return normalizedVec;
}

void Vec3::Normalize()
{
	D3DXVec3Normalize(this, this);
}

Vec3 Vec3::Scale(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

float Vec3::Dot(const Vec3& a, const Vec3& b)
{
	return D3DXVec3Dot(&a, &b);
}

Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	Vec3 result;
	D3DXVec3Cross(&result, &a, &b);
	return result;
}

Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, const float& t)
{
	Vec3 result;
	D3DXVec3Lerp(&result, &a, &b, t);
	return result;
}

Vec3 Vec3::ProjectOnVec3(const Vec3& a, const Vec3& vec3)
{
	return Dot(vec3, a) / Dot(vec3, vec3) * vec3;
}

Vec3 Vec3::ProjectOnPlane(const Vec3& a, const Vec3& n)
{
	return a - ProjectOnVec3(n, a);
}

float Vec3::Cos(const Vec3& from, const Vec3& to)
{
	return Dot(from.normalized(), to.normalized());
}

float Vec3::Radian(const Vec3& from, const Vec3& to)
{
	float demoninator = sqrtf(from.sqrMagnitude() * to.sqrMagnitude());
	if (demoninator < D3DX_16F_EPSILON)
		return 0;

	float dot = Dot(from, to);
	float cos = dot / demoninator;
	return acosf(cos);
}

float Vec3::Angle(const Vec3& from, const Vec3& to)
{
	return Radian(from, to) * 180.0f / D3DX_PI;
}

float Vec3::Distance(const Vec3& a, const Vec3& b)
{
	return (b - a).magnitude();
}

Vec3 Vec3::back()
{
	return Vec3(0, 0, -1);
}

Vec3 Vec3::down()
{
	return Vec3(0, -1, 0);
}

Vec3 Vec3::forawrd()
{
	return Vec3(0, 0, 1);
}

Vec3 Vec3::left()
{
	return Vec3(-1, 0, 0);
}

Vec3 Vec3::right()
{
	return Vec3(1, 0, 0);
}

Vec3 Vec3::up()
{
	return Vec3(0, 1, 0);
}

Vec3 Vec3::one()
{
	return Vec3(1, 1, 1);
}

Vec3 Vec3::zero()
{
	return Vec3(0, 0, 0);
}
