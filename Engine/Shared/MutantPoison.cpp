#include "shared_stdafx.h"
#include "MutantPoison.h"
#include "Player.h"
#include "MutantSpriteAnimator.h"
#include "GranadeTrail.h"
#include "PhysicsLayers.h"

void MutantPoison::Awake()
{
	auto trailObj = CreateGameObjectToChild(transform);

	m_moveSpeed = 8.0f;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localScale = Vec3::one() * 0.8f;
	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;



	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<MutantSpriteAnimator>();

	//{	// For debug
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	m_debugRenderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}
}

void MutantPoison::FixedUpdate()
{
#ifdef _AFX
	return;
#endif

	Collider* collider = Physics::OverlapSphere(
		transform->position,
		m_radius,
		(1 << (PxU32)PhysicsLayers::Terrain || 1 << (PxU32)PhysicsLayers::Player),
		PhysicsQueryType::Collider);

	if (collider)
	{
		if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
			gameObject->Destroy();
		}
		else if (collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{

		}
	}
}

void MutantPoison::Update()
{
#ifdef _AFX
	return;
#endif

	//m_animator->SetDefaultAnimation(m_animator->GetBullet(), true);
	m_animator->SetDefaultAnimation(m_animator->GetMutantPoison());


	Vec3 warmechPos = transform->position;
	Vec3 xzplayerPos = Vec3(Player::GetInstance()->transform->position.x, transform->position.y, Player::GetInstance()->transform->position.z);


	if (m_initialdir)
	{
		forward = xzplayerPos - warmechPos;
		forward.Normalize();
		m_initialdir = false;
	}

	transform->position += forward * m_moveSpeed * Time::DeltaTime();

	m_selfDestroyCounter -= Time::DeltaTime();

	if (m_selfDestroyCounter < 0)
	{
		gameObject->Destroy();
	}
}

void MutantPoison::LateUpdate()
{
#ifdef _AFX
	return;
#endif
}

void MutantPoison::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();

#ifdef _AFX
	return;
#endif
}

