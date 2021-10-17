#include "stdafx.h"
#include "WarmechBullet.h"
#include "WarmechSpriteAnimator.h"
#include "PhysicsLayers.h"

void WarmechBullet::Awake()
{
	m_moveSpeed = 3.0f;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localScale = Vec3::one() * 0.5f;	

	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();

	{	// For debug
		auto debugRendererObj = CreateGameObjectToChild(transform);
		m_debugRenderer = debugRendererObj->AddComponent<UserMeshRenderer>();
		m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
		m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		m_debugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}
}

void WarmechBullet::Update()
{

	m_animator->SetDefaultAnimation(m_animator->GetBullet(), true);

	transform->position += transform->forward * m_moveSpeed * Time::DeltaTime();

	m_selfDestroyCounter -= Time::DeltaTime();

	if (m_selfDestroyCounter < 0)
	{
		gameObject->Destroy();
	}
}

void WarmechBullet::LateUpdate()
{
	// For debug
	m_debugRenderer->transform->scale = Vec3::one() * m_radius;

	//Collider* collider = Physics::OverlapSphere(
	//	transform->position,
	//	m_radius,
	//	(1 << (PxU32)PhysicsLayers::Terrain || 1 << (PxU32)PhysicsLayers::Player),
	//	PhysicsQueryType::Collider);

	//if (collider)
	//{
	//	if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
	//	{

	//	}
	//	else if (collider->layerIndex == (uint8_t)PhysicsLayers::Player)
	//	{

	//	}
	//}
}

void WarmechBullet::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
