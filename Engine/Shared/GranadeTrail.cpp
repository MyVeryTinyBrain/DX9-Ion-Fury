#include "shared_stdafx.h"
#include "GranadeTrail.h"
#include "BillboardEffect.h"

void GranadeTrail::Update()
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

void GranadeTrail::MakeTrailEffectOnce()
{
	GameObject* effectObj = CreateGameObject();
	effectObj->transform->position = transform->position;
	effectObj->transform->scale = Vec3::one() * m_singleEffectScale;
	effectObj->transform->eulerAngle = Vec3(0, 0, float(rand() % 45));

	BillboardEffect* effect = effectObj->AddComponent<BillboardEffect>();
	effect->SetIgnoreZRotation(false);

	effect->AddTexture(L"../SharedResource/Texture/smoke0/0.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/1.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/2.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/3.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/4.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/5.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/6.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/7.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/8.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/9.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/10.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/11.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/12.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/13.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/14.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/15.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/16.png");
	effect->AddTexture(L"../SharedResource/Texture/smoke0/17.png");

	effect->FitIntervalToTime(m_singleEffectDuration);
}
