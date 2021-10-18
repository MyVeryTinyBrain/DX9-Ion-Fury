#include "stdafx.h"
#include "BloodEffect.h"
#include "BillboardEffect.h"

void BloodEffect::Awake()
{
	m_effect = gameObject->AddComponent<BillboardEffect>();

	wchar_t buffer0[256];
	wchar_t buffer1[256];
	wchar_t buffer2[256];
	wchar_t buffer3[256];

	int index = rand() % 3;

	swprintf_s(buffer0, L"../SharedResource/Texture/blood%d/0.png", index);
	swprintf_s(buffer1, L"../SharedResource/Texture/blood%d/1.png", index);
	swprintf_s(buffer2, L"../SharedResource/Texture/blood%d/2.png", index);
	swprintf_s(buffer3, L"../SharedResource/Texture/blood%d/3.png", index);

	m_effect->AddTexture(buffer0);
	m_effect->AddTexture(buffer1);
	m_effect->AddTexture(buffer2);
	m_effect->AddTexture(buffer3);

	gameObject->transform->scale = Vec3::one() * 2.0f;
}
