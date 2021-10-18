#include "stdafx.h"
#include "WarmechTrail.h"
#include "BillboardEffect.h"

void WarmechTrail::Update()
{
	if (m_makeEffectCounter <= 0)
	{
		MakeTrailEffectOnce();

		m_makeEffectCounter = m_delay;
	}

	if (m_makeEffectCounter > 0)
	{
		m_makeEffectCounter -= Time::DeltaTime();
	}
}

void WarmechTrail::MakeTrailEffectOnce()
{
	GameObject* effectObj = CreateGameObject();
	effectObj->transform->position = transform->position;
	effectObj->transform->scale = Vec3::one() * m_singleEffectScale;
	effectObj->transform->eulerAngle = Vec3(0, 0, float(rand() % 45));

	BillboardEffect* effect = effectObj->AddComponent<BillboardEffect>();
	effect->SetIgnoreZRotation(false);

	effect->AddTexture(L"../SharedResource/Texture/wermech_weapon/warmechEffect.png");

	effect->FitIntervalToTime(m_singleEffectDuration);
}
