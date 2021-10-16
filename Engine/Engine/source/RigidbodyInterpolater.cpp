#include "EngineBase.h"
#include "RigidbodyInterpolater.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "CentralTimeElement.h"

RigidbodyInterpolater::RigidbodyInterpolater(Rigidbody* body) : RigibdoyInterpolateBase(body)
{
}

void RigidbodyInterpolater::Enable()
{
	BackupPose();

	m_beforePosition = m_backupPosition;
	m_beforeRotation = m_backupRotation;
}

void RigidbodyInterpolater::BackupPose()
{
	m_beforePosition = m_backupPosition;
	m_beforeRotation = m_backupRotation;

	m_backupPosition = m_body->transform->position;
	m_backupRotation = m_body->transform->rotation;

	m_originBackupPosition = m_backupPosition;
	m_originBackupRotation = m_backupRotation;
}

void RigidbodyInterpolater::RollbackPose()
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

void RigidbodyInterpolater::InterpolatePose()
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

void RigidbodyInterpolater::CheckPoseChange()
{
	Vec3 deltaPos = m_body->transform->position - CalcInterpolatePosition();
	if (deltaPos.magnitude() > 0.001f)
	{
		m_backupPosition += deltaPos;
		m_beforePosition += deltaPos;
	}

	Quat deltaRotation = CalcInterpolateRotation().inversed() * m_body->transform->rotation;
	float deltaAngle = Quat::Angle(Quat::Identity(), deltaRotation);
	if (deltaAngle > 0.1f)
	{
		m_backupRotation = deltaRotation * m_backupRotation;
		m_beforeRotation = deltaRotation * m_beforeRotation;
	}
}

Vec3 RigidbodyInterpolater::CalcInterpolatePosition() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated() * centralTime->GetFixedUpdateTimeScale();
	float percent = accumulated / centralTime->GetFixedUpdateInterval();

	return Vec3::Lerp(m_beforePosition, m_backupPosition, percent);
}

Quat RigidbodyInterpolater::CalcInterpolateRotation() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated() * centralTime->GetFixedUpdateTimeScale();
	float percent = accumulated / centralTime->GetFixedUpdateInterval();

	return Quat::SLerp(m_beforeRotation, m_backupRotation, percent);
}
