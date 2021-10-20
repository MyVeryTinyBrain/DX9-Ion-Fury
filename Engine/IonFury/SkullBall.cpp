#include "stdafx.h"
#include "SkullBall.h"
#include "BillboardEffect.h"
#include "SkullBallAnimator.h"
#include <PhysicsLayers.h>
#include <Player.h>

void SkullBall::Awake()
{
	m_root = CreateGameObjectToChild(transform);

	m_renderer = m_root->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_renderer->material = Resource::FindAs<Material>(BuiltInNolightAlphaTestMaterial);

	m_root->AddComponent<SkullBallAnimator>();

	//{
	//	auto debugObj = CreateGameObjectToChild(m_root->transform);
	//	debugObj->transform->scale = Vec3::one() * m_triggerRadius * 2.0f;
	//	m_debugRenderer = debugObj->AddComponent<UserMeshRenderer>();
	//	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//}
}

void SkullBall::LateUpdate()
{
	transform->position += m_velocity * Time::DeltaTime();

	Collider* collider = TriggerCheck();

	if (collider)
	{
		OnTrigger(collider);
	}
}

void SkullBall::SetVelocity(const Vec3& value)
{
	m_velocity = value;
}

const Vec3& SkullBall::GetVelocity() const
{
	return m_velocity;
}

Collider* SkullBall::TriggerCheck()
{
	Collider* collider = Physics::OverlapSphere(
		transform->position,
		m_triggerRadius,
		(1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player),
		PhysicsQueryType::Collider);

	return collider;
}

void SkullBall::OnTrigger(Collider* collider)
{
	if (!collider)
	{
		return;
	}

	if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
	{

	}
	else if(collider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		Player::GetInstance()->TakeDamage(1);
	}

	MakeExplosionEffect();

	gameObject->Destroy();
}

void SkullBall::MakeExplosionEffect()
{
	GameObject* effectObj = CreateGameObject();
	effectObj->transform->position = transform->position;
	effectObj->transform->scale = Vec3::one() * 2.5f;

	BillboardEffect* effect = effectObj->AddComponent<BillboardEffect>();
	effect->AddTexture(L"../SharedResource/Texture/explosion2/0.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/1.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/2.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/3.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/4.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/5.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/6.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/7.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/8.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/9.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/10.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/11.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/12.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion2/13.png");
}
