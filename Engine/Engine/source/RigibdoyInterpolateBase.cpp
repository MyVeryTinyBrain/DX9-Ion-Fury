#include "EngineBase.h"
#include "RigibdoyInterpolateBase.h"

RigibdoyInterpolateBase::RigibdoyInterpolateBase(Rigidbody* body)
{
	m_body = body;
}

bool RigibdoyInterpolateBase::IsInterpolatePosition() const
{
	return m_interpolatePoisiton;
}

bool RigibdoyInterpolateBase::IsInterpolateRotation() const
{
	return m_interpolateRotation;
}

void RigibdoyInterpolateBase::SetInterpolatePositionMode(bool value)
{
	m_interpolatePoisiton = value;
}

void RigibdoyInterpolateBase::SetInterpolateRotationMode(bool value)
{
	m_interpolateRotation = value;
}
