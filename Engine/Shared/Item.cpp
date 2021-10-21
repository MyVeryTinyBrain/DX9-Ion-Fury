#include "shared_stdafx.h"
#include "Item.h"
#include "PhysicsLayers.h"
#include "Player.h"

void Item::Awake()
{
	m_root = CreateGameObjectToChild(transform);

	m_renderer = m_root->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->SetTexture(0, Resource::FindAs<Texture>(InitTextureLocalPath()));
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_renderer->material = Resource::FindAs<Material>(BuiltInAlphaTestMaterial);

	//{
	//	auto debugObj = CreateGameObjectToChild(m_root->transform);
	//	m_debugRenderer = debugObj->AddComponent<UserMeshRenderer>();
	//	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//}
}

void Item::Start()
{
	if (Time::TimeScale() == 0)
	{
		return;
	}

	PhysicsRay ray(transform->position, Vec3::down(), 50.0f);
	RaycastHit hit;
	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider))
	{
		transform->position = hit.point + Vec3::up() * m_triggerRadius;
	}
}

void Item::Update()
{
	if (Time::TimeScale() == 0)
	{
		return;
	}

	auto collider = Physics::OverlapSphere(
		transform->position,
		m_triggerRadius,
		(1 << (int)PhysicsLayers::Player),
		PhysicsQueryType::Collider
	);

	if (collider)
	{
		OnTrigger(Player::GetInstance());
		gameObject->Destroy();
	}

	if (m_debugRenderer)
	{
		m_debugRenderer->transform->scale = Vec3::one() * m_triggerRadius * 2.0f;
	}
}
