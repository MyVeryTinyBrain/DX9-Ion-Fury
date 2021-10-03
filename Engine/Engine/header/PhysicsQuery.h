#pragma once

namespace PhysicsQuery
{
	bool Raycast(const Vec3& rayPoint, const Vec3& rayDir, float maxDistance, PxU32 layerMask);
};

