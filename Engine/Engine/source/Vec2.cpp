#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "Vec2.h"

using namespace MathEx;

Vec2::Vec2()
{
	x = y = 0;
}

Vec2::Vec2(const FLOAT* pf) : Base(pf)
{
}

Vec2::Vec2(const D3DXVECTOR2& v) : Base(v)
{
}

Vec2::Vec2(const D3DXVECTOR3& v) : Base(v.x, v.y)
{
}

Vec2::Vec2(const D3DXVECTOR4& v) : Base(v.x, v.y)
{
}

Vec2::Vec2(const D3DXFLOAT16* pf) : Base(pf)
{
}

Vec2::Vec2(const FLOAT& x, const FLOAT& y) : Base(x, y)
{
}

Vec2::Vec2(const POINT& pt)
{
	x = float(pt.x);
	y = float(pt.y);
}

Vec2::operator FLOAT* ()
{
	return Base::operator FLOAT * ();
}

Vec2::operator const FLOAT* () const
{
	return Base::operator const FLOAT * ();
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2& Vec2::operator*=(const FLOAT& s)
{
	x *= s;
	y *= s;
	return *this;
}

Vec2& Vec2::operator/=(const FLOAT& s)
{
	x /= s;
	y /= s;
	return *this;
}

Vec2 Vec2::operator+() const
{
	return { +x,+y };
}

Vec2 Vec2::operator-() const
{
	return { -x,-y };
}

Vec2 Vec2::operator+(const Vec2& v) const
{
	return { x + v.x,y + v.y };
}

Vec2 Vec2::operator-(const Vec2& v) const
{
	return { x - v.x,y - v.y };
}

Vec2 Vec2::operator*(const FLOAT& s) const
{
	return { x * s,y * s };
}

Vec2 Vec2::operator/(const FLOAT& s) const
{
	return { x / s,y / s };
}

Vec2 operator*(const FLOAT& s, const Vec2& v)
{
	return { v.x * s,v.y * s };
}

BOOL Vec2::operator==(const Vec2& v) const
{
	return (x == v.x) && (y == v.y);
}

BOOL Vec2::operator!=(const Vec2& v) const
{
	return !(*this == v);
}

Vec2::operator D3DXVECTOR2() const
{
	return D3DXVECTOR2(x, y);
}

Vec2::operator D3DXVECTOR3() const
{
	return D3DXVECTOR3(x, y, 0);
}

Vec2::operator D3DXVECTOR4() const
{
	return D3DXVECTOR4(x, y, 0, 0);
}

Vec2::operator POINT() const
{
	return POINT{ LONG(x), LONG(y) };
}

float Vec2::sqrMagnitude() const
{
	return D3DXVec2LengthSq(this);
}

float Vec2::magnitude() const
{
	return D3DXVec2Length(this);
}

Vec2 Vec2::normalized() const
{
	Vec2 normalizedVec;
	D3DXVec2Normalize(&normalizedVec, this);
	return normalizedVec;
}

void Vec2::Normalize()
{
	D3DXVec2Normalize(this, this);
}

Vec2 Vec2::Scale(const Vec2& a, const Vec2& b)
{
	return Vec2(a.x * b.x, a.y * b.y);
}

float Vec2::Dot(const Vec2& a, const Vec2& b)
{
	return D3DXVec2Dot(&a, &b);
}

D3DXVECTOR3 Vec2::Cross(const Vec2& a, const Vec2& b)
{
	D3DXVECTOR3 result;
	D3DXVECTOR3 _a = a;
	D3DXVECTOR3 _b = b;
	D3DXVec3Cross(&result, &_a, &_b);
	return result;
}

Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b, const float& t)
{
	Vec2 result;
	D3DXVec2Lerp(&result, &a, &b, t);
	return result;
}

Vec2 Vec2::ProjectOnVec2(const Vec2& a, const Vec2& vec2)
{
	return Dot(vec2, a) / Dot(vec2, vec2) * vec2;
}

float Vec2::Cos(const Vec2& from, const Vec2& to)
{
	return Dot(from.normalized(), to.normalized());
}

float Vec2::Radian(const Vec2& from, const Vec2& to)
{
	float demoninator = sqrtf(from.sqrMagnitude() * to.sqrMagnitude());
	if (demoninator < D3DX_16F_EPSILON)
		return 0;

	float dot = Dot(from, to);
	float cos = dot / demoninator;
	return acosf(cos);
}

float Vec2::Angle(const Vec2& from, const Vec2& to)
{
	return Radian(from, to) * 180.0f / D3DX_PI;
}

float Vec2::Angle180(const Vec2& dir)
{
	float angle = Vec2::Angle(Vec2::right(), dir);
	if (dir.y < 0) angle *= -1;
	return angle;
}

float Vec2::Angle360(const Vec2& dir)
{
	float angle = Vec2::Angle(Vec2::right(), dir);
	if (dir.y < 0) angle = 360 - angle;
	return angle;
}

float Vec2::Distance(const Vec2& a, const Vec2& b)
{
	return (b - a).magnitude();
}

float Vec2::SqrDistance(const Vec2& a, const Vec2& b)
{
	return (b - a).sqrMagnitude();
}

Vec2 Vec2::down()
{
	return Vec2(0, -1);
}

Vec2 Vec2::left()
{
	return Vec2(-1, 0);
}

Vec2 Vec2::right()
{
	return Vec2(1, 0);
}

Vec2 Vec2::up()
{
	return Vec2(0, 1);
}

Vec2 Vec2::one()
{
	return Vec2(1, 1);
}

Vec2 Vec2::zero()
{
	return Vec2(0, 0);
}

Vec2 Vec2::Direction(const float& angle)
{
	return Vec2(cosf(angle * Deg2Rad), sinf(angle * Deg2Rad));
}
