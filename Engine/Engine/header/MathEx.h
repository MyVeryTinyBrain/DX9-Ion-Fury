#pragma once

namespace MathEx
{
	constexpr float PI = 3.141592654f;
	constexpr float TAU = PI * 2.0f;
	constexpr float Epsilon = 4.8875809e-4f;
	constexpr float Deg2Rad = (PI / 180.0f);
	constexpr float Rad2Deg = (180.0f / PI);

	float Lerp(float from, float to, float t);

	float Clamp(float value, float min, float max);

	float Clamp01(float value, float min, float max);

	float Closet(float value, float min, float max);

	float DeltaAngle(float from, float to);

	float Repeat(float value, float max);

	float Max(float a, float b);

	float Min(float a, float b);

	float Abs(float value);

	bool LineIntersection(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, const D3DXVECTOR2& p3, const D3DXVECTOR2& p4, D3DXVECTOR2* pResult);
	
	bool LineSegmentIntersection(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, const D3DXVECTOR2& p3, const D3DXVECTOR2& p4, D3DXVECTOR2* pResult);
	
	D3DXVECTOR4 BezierCurve2(const D3DXVECTOR4& p1, const D3DXVECTOR4& p2, const D3DXVECTOR4& p3, float t);
	
	D3DXVECTOR4 BezierCurve3(const D3DXVECTOR4& p1, const D3DXVECTOR4& p2, const D3DXVECTOR4& p3, const D3DXVECTOR4& p4, float t);

	// 본래 평면의 노멀과 레이의 방향이 서로 수직이면 교점은 없습니다.
	// 이 함수에서는 임의로 레이의 방향을 미세하게 조정하여 교점을 생성합니다.
	// 생성된 교점을 만들어내는 스칼라 t 값을 반환합니다.
	// 교점 공식: rayPoint + rayDirection * t
	float RaycastOnPlane(const Vec3& planeNormal, const Vec3& planePoint, const Vec3& rayPoint, const Vec3& rayDirection);
}