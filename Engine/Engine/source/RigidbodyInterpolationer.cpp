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
	m_backupEulerAngle = m_body->transform->eulerAngle;
}

void RigidbodyInterpolationer::RollbackPose()
{
	m_body->transform->position = m_backupPosition;
	m_body->transform->eulerAngle = m_backupEulerAngle;
}

void RigidbodyInterpolationer::InterpolatePose()
{
	m_body->transform->position = CalcInterpolatePosition();
	m_body->transform->eulerAngle = CalcInterpolateEulerAngle();
}

void RigidbodyInterpolationer::CheckPoseChange()
{
	Vec3 deltaPos = m_body->transform->position - CalcInterpolatePosition();
	if (deltaPos.magnitude() > 0.001f)
	{
		m_backupPosition += deltaPos;
	}

	Vec3 deltaAngle = m_body->transform->eulerAngle - CalcInterpolateEulerAngle();
	if (Abs(deltaAngle.x) > 0.1f)
	{
		m_backupEulerAngle.x += deltaAngle.x;
	}
	if (Abs(deltaAngle.y) > 0.1f)
	{
		m_backupEulerAngle.y += deltaAngle.y;
	}
	if (Abs(deltaAngle.z) > 0.1f)
	{
		m_backupEulerAngle.z += deltaAngle.z;
	}
}

Vec3 RigidbodyInterpolationer::CalcInterpolatePosition() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated();

	//accumulated = Clamp(accumulated, 0, centralTime->GetFixedUpdateInterval());

	return m_backupPosition + m_body->velocity * accumulated;
}

Vec3 RigidbodyInterpolationer::CalcInterpolateEulerAngle() const
{
	auto centralTime = CentralTimeElement::GetInstance();
	float accumulated = centralTime->GetFixedUpdateAccumulated();

	//accumulated = Clamp(accumulated, 0, centralTime->GetFixedUpdateInterval());

	return m_backupEulerAngle + m_body->angularVelocity * accumulated;
}
