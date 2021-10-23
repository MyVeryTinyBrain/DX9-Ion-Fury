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
	if (Time::FixedTimeScale() == 0)
		return;

	Collider* collider = Physics::OverlapSphere(
		m_radius,
		transform->position,
		(1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player),
		PhysicsQueryType::Collider);


	if (collider)
	{
		if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
			gameObject->Destroy();
		}
		if (collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			ShootToPlayer();
			gameObject->Destroy();
		}
	}
}

void MutantPoison::Update()
{
	if (Time::TimeScale() == 0)
		return;

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

	if (m_selfDestroyCounter <= 0)
	{
		gameObject->Destroy();
	}
}

void MutantPoison::LateUpdate()
{
	if (Time::TimeScale() == 0)
		return;
}

void MutantPoison::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();

	if (Time::TimeScale() == 0)
		return;
}

void MutantPoison::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(1);
}

Vec3 MutantPoison::GetXZDirection(const Vec3& point) const
{
	Vec3 posxz = transform->position;
	posxz.y = 0;

	Vec3 targetxz = point;
	targetxz.y = 0;

	Vec3 rel = targetxz - posxz;
	Vec3 dir = rel.normalized();

	return dir;
}
