#pragma once

#include "Collider.h"

class CapsuleCollider : public Collider
{
	virtual PxGeometryHolder CreateGeometry() override;

public:

	float GetRadius() const;

	void SetRadius(float value);

	float GetHalfHeight() const;

	void SetHalfHeight(float value);

	__declspec(property(get = GetRadius, put = SetRadius)) float radius;

	__declspec(property(get = GetHalfHeight, put = SetHalfHeight)) float halfHeight;

private:

	PxCapsuleGeometry CreateCapsuleGeometry() const;

	float GetBiggestLengthFromAbsVec3XZ(const Vec3& value) const;

private:

	float m_radius = 0.5f;

	float m_halfHeight = 0.5f;
};

