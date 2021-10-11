#pragma once

enum class PhysicsQueryType
{
	None = 0,
	Collider = 1 << 0,
	Trigger = 1 << 1,
	All = Collider | Trigger,
};

struct PhysicsRay
{
	PhysicsRay() {};
	PhysicsRay(const Vec3& point, const Vec3& direction);
	PhysicsRay(const Vec3& point, const Vec3& direction, float distance);

	Vec3 point;
	Vec3 direction;
	float distance = FLT_MAX;
};

struct RaycastHit
{
	Vec3 point;
	Vec3 normal;
	float distance;
	class Collider* collider = nullptr;
};

struct SweepHit
{
	Vec3 point;
	Vec3 normal;
	float distance;
	class Collider* collider = nullptr;
};

