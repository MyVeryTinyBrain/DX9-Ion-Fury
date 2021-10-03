#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
	virtual PxGeometryHolder CreateGeometry() override;

public:

	void SetExtents(const Vec3& extents);

	const Vec3& GetExtents() const;

	__declspec(property(get = GetExtents, put = SetExtents)) const Vec3& extents;

private:

	PxBoxGeometry CreateBoxGeometry() const;

private:

	Vec3 m_extents = Vec3(1, 1, 1);
};

