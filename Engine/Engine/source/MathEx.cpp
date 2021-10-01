#include "EngineBase.h"
#include "D3DXMathEx.h"
#include "MathEx.h"

float MathEx::Lerp(float from, float to, float t)
{
	return from + (to - from) * t;
}

float MathEx::Clamp(float value, float min, float max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

float MathEx::Clamp01(float value, float min, float max)
{
	value = Clamp(value, min, max);
	float delta = max - min;
	float valueFromMin = value - min;
	float percent = valueFromMin / delta;
	return percent;
}

float MathEx::Closet(float value, float min, float max)
{
	float toMin = fabsf(value - min);
	float toMax = fabsf(value - max);
	if (toMin < toMax) return min;
	else return max;
}

float MathEx::DeltaAngle(float from, float to)
{
	//float delta = fmodf(to - from, 360.0f);
	float delta = to - from;
	while (delta > 180.0f)
		delta -= 360.0f;
	while (delta < -180.0f)
		delta += 360.0f;
	return delta;
}

float MathEx::Repeat(float value, float max)
{
	return fmodf(value, max);
}

float MathEx::Max(float a, float b)
{
	return a >= b ? a : b;
}

float MathEx::Min(float a, float b)
{
	return a <= b ? a : b;
}

float MathEx::Abs(float value)
{
	if (value < 0)
		return -value;
	return value;
}

bool MathEx::LineIntersection(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, const D3DXVECTOR2& p3, const D3DXVECTOR2& p4, D3DXVECTOR2* pResult)
{
	float bx = p2.x - p1.x;
	float by = p2.y - p1.y;
	float dx = p4.x - p3.x;
	float dy = p4.y - p3.y;
	float bDotDPerp = bx * dy - by * dx;
	if (bDotDPerp == 0)
	{
		return false;
	}
	float cx = p3.x - p1.x;
	float cy = p3.y - p1.y;
	float t = (cx * dy - cy * dx) / bDotDPerp;

	pResult->x = p1.x + t * bx;
	pResult->y = p1.y + t * by;
	return true;
}

bool MathEx::LineSegmentIntersection(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, const D3DXVECTOR2& p3, const D3DXVECTOR2& p4, D3DXVECTOR2* pResult)
{
	float bx = p2.x - p1.x;
	float by = p2.y - p1.y;
	float dx = p4.x - p3.x;
	float dy = p4.y - p3.y;
	float bDotDPerp = bx * dy - by * dx;
	if (bDotDPerp == 0)
	{
		return false;
	}
	float cx = p3.x - p1.x;
	float cy = p3.y - p1.y;
	float t = (cx * dy - cy * dx) / bDotDPerp;
	if (t < 0 || t > 1)
	{
		return false;
	}
	float u = (cx * by - cy * bx) / bDotDPerp;
	if (u < 0 || u > 1)
	{
		return false;
	}

	pResult->x = p1.x + t * bx;
	pResult->y = p1.y + t * by;
	return true;
}

D3DXVECTOR4 MathEx::BezierCurve2(const D3DXVECTOR4& p1, const D3DXVECTOR4& p2, const D3DXVECTOR4& p3, float t)
{
	Vec4 a1 = Vec4::Lerp(p1, p2, t);
	Vec4 a2 = Vec4::Lerp(p2, p3, t);
	Vec4 b1 = Vec4::Lerp(a2, a2, t);
	return b1;
}

D3DXVECTOR4 MathEx::BezierCurve3(const D3DXVECTOR4& p1, const D3DXVECTOR4& p2, const D3DXVECTOR4& p3, const D3DXVECTOR4& p4, float t)
{
	Vec4 a1 = Vec4::Lerp(p1, p2, t);
	Vec4 a2 = Vec4::Lerp(p2, p3, t);
	Vec4 a3 = Vec4::Lerp(p3, p4, t);
	Vec4 b1 = Vec4::Lerp(a1, a2, t);
	Vec4 b2 = Vec4::Lerp(a2, a3, t);
	Vec4 c1 = Vec4::Lerp(b1, b2, t);
	return c1;
}

float MathEx::RaycastOnPlane(const Vec3& planeNormal, const Vec3& planePoint, const Vec3& rayPoint, const Vec3& rayDirection)
{
	if (rayDirection.sqrMagnitude() == 0)
		return 0;

	if (planeNormal.sqrMagnitude() == 0)
		return 0;

	float nDotV = Vec3::Dot(planeNormal, rayDirection);
	if (nDotV == 0)
	{
		Vec3 newRayDir = rayDirection + Vec3(+0.0001f, -0.0001f, +0.0001f);
		nDotV = Vec3::Dot(planeNormal, newRayDir);
	}

	float top = Vec3::Dot(planeNormal, planePoint - rayPoint);

	return top / nDotV;
}
