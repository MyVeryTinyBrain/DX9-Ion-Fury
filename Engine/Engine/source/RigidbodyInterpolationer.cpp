#include "EngineBase.h"
#include "RigidbodyInterpolationer.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "CentralTimeElement.h"

RigidbodyInterpolationer::RigidbodyInterpolationer(Rigidbody* body)
{
	m_body = body;
}

void RigidbodyInterpolationer::BackupPose()
{
	m_backupPosition = m_body->transform->position;
	m_backupRotation = m_body->transform->rotation;
}

void RigidbodyInterpolationer::RollbackPose()
{
	if (m_interpolatePoisiton)
	{
		m_body->transform->position = m_backupPosition;
	}
	
	if (m_interpolateRotation)
	{
		m_body->transform->rotation = m_backupRotation;
	}
}

void RigidbodyInterpolationer::InterpolatePose()
{
	if (m_interpolatePoisiton)
	{
		m_body->transform->position = CalcInterpolatePosition();
	}
	
	if (m_interpolateRotation)
	{
		m_body->transform->rotation = CalcInterpolateRotation();
	}
}

void RigidbodyInterpolationer::CheckPoseChange()
{
	Vec3 deltaPos = m_body->transform->position - CalcInterpolatePosition();
	if (deltaPos.magnitude() > 0.001f)
	{
		m_backupPosition += deltaPos;
	}

	Quat deltaRotation = CalcInterpolateRotation().inversed() * m_body->transform->rotation;
	float deltaAngle = Quat::Angle(Quat::Identity(), deltaRotation);
	if (deltaAngle > 0.1f)
	{
		wstring name = m_body->name;
		m_backupRotation = deltaRotation * m_backupRotation;
	}
}

bool RigidbodyInterpolationer::IsInterpolatePosition() const
{
	return m_interpolatePoisiton;
}

bool RigidbodyInterpolationer::IsInterpolateRotation() const
{
	return m_interpolateRotation;
}

void RigidbodyInterpolationer::SetInterpolatePositionMode(bool value)
{
	m_interpolatePoisiton = value;
}

void RigidbodyInterpolationer::SetInterpolateRotationMode(bool value)
{
	m_interpolateRotation = value;
}

Vec3 RigidbodyInterpolationer::CalcInterpolatePosition() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated() * centralTime->GetFixedUpdateTimeScale();

	//accumulated = Clamp(accumulated, 0, centralTime->GetFixedUpdateInterval());

	return m_backupPosition + m_body->velocity * accumulated;
}

Quat RigidbodyInterpolationer::CalcInterpolateRotation() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated() * centralTime->GetFixedUpdateTimeScale();

	//accumulated = Clamp(accumulated, 0, centralTime->GetFixedUpdateInterval());

	Quat q = Quat::FromEuler(
		m_body->angularVelocity.x * accumulated,
		m_body->angularVelocity.y * accumulated,
		m_body->angularVelocity.z * accumulated
	);

	Quat res = q * m_backupRotation;

	return res;
}
