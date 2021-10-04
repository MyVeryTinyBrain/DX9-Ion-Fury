#pragma once

enum class PhysicsQueryType
{
	None = 0,
	Collider = 1 << 0,
	Trigger = 1 << 1,
	All = Collider | Trigger,
};

struct RaycastHit
{
	Vec3 point;
	Vec3 normal;
	float distance;
	class Collider* collider = nullptr;
};

