#include "shared_stdafx.h"
#include "WarmechBullet.h"
#include "WarmechSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "WarmechTrail.h"

void WarmechBullet::Awake()
{
	auto trailObj = CreateGameObjectToChild(transform);
	WarmechTrail* trail = trailObj->AddComponent<WarmechTrail>();

	m_moveSpeed = 7.0f;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localScale = Vec3::one() * 0.1f;


	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_colliderObj = CreateGameObjectToChild(gameObject->transform);
	m_collider = m_colliderObj->AddComponent<SphereCollider>();
	m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &WarmechBullet::OnCollisionEnter);

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();

	{	// For debug
		auto debugRendererObj = CreateGameObjectToChild(m_collider->transform);
		m_debugRenderer = debugRendererObj->AddComponent<UserMeshRenderer>();
		m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
		m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		m_debugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}
}

void WarmechBullet::FixedUpdate()
{
	Collider* collider = Physics::OverlapSphere(
		m_radius,
		transform->position,
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

void WarmechBullet::Update()
{

	m_animator->SetDefaultAnimation(m_animator->GetSpriteAnimation(SPRITE_WARMECH::Bullet), true);


	Vec3 warmechPos = transform->position;
	//Vec3 xzplayerPos = Vec3(Player::GetInstance()->transform->position.x, transform->position.y , Player::GetInstance()->transform->position.z);
	Vec3 xzplayerPos = Player::GetInstance()->transform->position + Vec3::up() * 0.5f;

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

void WarmechBullet::LateUpdate()
{
	// For debug
	//m_debugRenderer->transform->scale = Vec3::one() * m_radius;

}

void WarmechBullet::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();

	if (m_collider)
	{
		m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &WarmechBullet::OnCollisionEnter);

		m_collider->Destroy();

		m_collider = nullptr;
	}

}

void WarmechBullet::OnCollisionEnter(const CollisionEnter& collider)
{
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		Player::GetInstance()->TakeDamage(1);
	}
}
