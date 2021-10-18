#include "EngineBase.h"
#include "RigidbodyExtrapolater.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "CentralTimeElement.h"

RigidbodyExtrapolater::RigidbodyExtrapolater(Rigidbody* body) : RigibdoyInterpolateBase(body)
{
}

void RigidbodyExtrapolater::Enable()
{
	BackupPose();
}

void RigidbodyExtrapolater::BackupPose()
{
	m_backupPosition = m_body->transform->position;
	m_backupRotation = m_body->transform->rotation;
}

void RigidbodyExtrapolater::RollbackPose()
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

void RigidbodyExtrapolater::InterpolatePose()
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

void RigidbodyExtrapolater::CheckPoseChange()
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
		m_backupRotation = deltaRotation * m_backupRotation;
	}
}

Vec3 RigidbodyExtrapolater::CalcInterpolatePosition() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated() * centralTime->GetFixedUpdateTimeScale();

	return m_backupPosition + m_body->velocity * accumulated;
}

Quat RigidbodyExtrapolater::CalcInterpolateRotation() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated() * centralTime->GetFixedUpdateTimeScale();

	Quat q = Quat::FromEuler(
		m_body->angularVelocity.x * accumulated,
		m_body->angularVelocity.y * accumulated,
		m_body->angularVelocity.z * accumulated
	);

	Quat res = q * m_backupRotation;

	return res;
}
