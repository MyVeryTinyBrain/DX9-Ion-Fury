#include "EngineBase.h"
#include "PhysicsQueryTypes.h"

PhysicsRay::PhysicsRay(const Vec3& point, const Vec3& direction)
{
	this->point = point;
	this->direction = direction;
}

PhysicsRay::PhysicsRay(const Vec3& point, const Vec3& direction, float distance)
{
	this->point = point;
	this->direction = direction;
	this->distance = distance;
}