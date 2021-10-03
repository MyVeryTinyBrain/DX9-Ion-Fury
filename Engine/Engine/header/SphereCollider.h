#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
	virtual PxGeometryHolder CreateGeometry() override;

public:

	float GetRadius() const;

	void SetRadius(float value);

	__declspec(property(get = GetRadius, put = SetRadius)) float radius;

private:

	PxSphereGeometry CreateSphereGeometry() const;

	float GetBiggestLengthFromAbsVec3(const Vec3& value) const;

private:

	float m_radius = 0.5f;
};

