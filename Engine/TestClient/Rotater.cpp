#include "stdafx.h"
#include "Rotater.h"

void Rotater::Awake()
{
	m_value = 0;

	m_dtScale = 1;
}

void Rotater::Update()
{
	float angSpeed = 45;

	Vec3 ang = transform->eulerAngle;

	ang.x -= angSpeed * Time::DeltaTime() * 0.5f * m_dtScale;
	ang.y -= angSpeed * Time::DeltaTime() * m_dtScale;
	ang.z -= angSpeed * Time::DeltaTime() * 1.5f * m_dtScale;

	transform->eulerAngle = ang;
}

void Rotater::OnWake()
{
	transform->eulerAngle = Vec3(0, 0, 0);
}
