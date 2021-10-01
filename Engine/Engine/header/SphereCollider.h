#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:

	float GetRadius() const;

	void SetRadius(float value);

	__declspec(property(get = GetRadius, put = SetRadius)) float radius;

private:

	virtual PxGeometry* CreateGeometry() override;

	virtual void OnBeginPhysicsSimulate() override;

	virtual void UpdateScale(const Vec3& scale) override;

	float GetBiggestAbsVec3(const Vec3& value) const;

private:

	float m_radius = 0.5f;
};

