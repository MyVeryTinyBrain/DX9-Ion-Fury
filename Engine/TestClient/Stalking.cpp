#include "stdafx.h"
#include "Stalking.h"

void Stalking::Update()
{
	if (!m_target)
		return;

	Vec3 rel = m_target->position - transform->position;
	Vec3 dir = rel.normalized();

	transform->position += dir * Time::DeltaTime() * 2.0f;

	if (Input::GetKeyDown(Key::Space) && !m_target.IsNull())
	{
		m_target->Destroy();
	}
}
