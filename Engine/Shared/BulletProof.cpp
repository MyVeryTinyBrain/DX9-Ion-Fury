#include "shared_stdafx.h"
#include "BulletProof.h"
#include "BillboardEffect.h"

void BulletProof::Awake()
{
	m_renderer = gameObject->AddComponent<UserMeshRenderer>();
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_renderer->material = Resource::FindAs<Material>(BuiltInNolightAlphaTestMaterial);

	int imageIndex = rand() % 5;
	wchar_t buffer[256];
	swprintf_s(buffer, L"../SharedResource/Texture/bulletproof/bulletproof%d.png", imageIndex);
	m_renderer->SetTexture(0, Resource::FindAs<Texture>(buffer));
}

void BulletProof::Update()
{
	if (m_selfDestroyCounter > float(BULLETPROOF_SELF_DESTROY_TIME))
	{
		gameObject->Destroy();
		return;
	}

	m_selfDestroyCounter += Time::DeltaTime();
}

void BulletProof::InitializeBulletProof(const Vec3& point, const Vec3& normal)
{
	float randomPull = float(rand() % 1000) / 1000.0f;
	randomPull *= 0.01f;

	transform->scale = Vec3::one() * 0.3f;
	transform->position = point + normal * (0.01f + randomPull);
	transform->forward = -normal;

	MakeEffectOnce(point + normal * 0.1f);
}

void BulletProof::MakeEffectOnce(const Vec3 point)
{
	GameObject* effectObj = CreateGameObject();
	effectObj->transform->position = transform->position;
	effectObj->transform->scale = Vec3::one() * 1.0f;
	effectObj->transform->eulerAngle = Vec3(0, 0, float(rand() % 360));

	BillboardEffect* effect = effectObj->AddComponent<BillboardEffect>();
	effect->SetIgnoreZRotation(false);

	effect->AddTexture(L"../SharedResource/Texture/spark0/3.png");
	effect->AddTexture(L"../SharedResource/Texture/spark0/4.png");
	effect->AddTexture(L"../SharedResource/Texture/spark0/5.png");
	effect->AddTexture(L"../SharedResource/Texture/spark0/6.png");
	effect->AddTexture(L"../SharedResource/Texture/spark0/7.png");
	effect->AddTexture(L"../SharedResource/Texture/spark0/8.png");
	effect->AddTexture(L"../SharedResource/Texture/spark0/9.png");

	float randomPercent = float(rand() % 100) * 0.01f;
	effect->FitIntervalToTime(randomPercent * 0.3f + 0.1f);
}