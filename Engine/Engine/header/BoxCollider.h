#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:

	const Vec3& GetExtents() const;

	void SetExtents(const Vec3& value);

	__declspec(property(get = GetExtents, put = SetExtents)) const Vec3& extents;

private:

	virtual PxGeometry* CreateGeometry() override;

	virtual void OnBeginPhysicsSimulate() override;

	virtual void UpdateScale(const Vec3& scale) override;
	
private:

	Vec3 m_extents = Vec3::one();
};

