#include "EngineBase.h"
#include "Types.h"

Ray::Ray(const Vec3& point, const Vec3& direction)
{
	this->point = point;
	this->direction = direction;
}

Ray::Ray(const Vec3& point, const Vec3& direction, float distance)
{
	this->point = point;
	this->direction = direction;
	this->distance = distance;
}
