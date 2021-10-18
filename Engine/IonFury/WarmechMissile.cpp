#include "stdafx.h"
#include "WarmechMissile.h"
#include "WarmechSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "GranadeTrail.h"
#include "WarmechExplosion.h"


void WarmechMissile::Awake()
{
	auto trailObj = CreateGameObjectToChild(transform);
	GranadeTrail* trail = trailObj->AddComponent<GranadeTrail>();

	m_moveSpeed = 3.0f;

	m_body = gameObject->AddComponent<Rigidbody>();

	m_body->mass = 0.1f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->positionIteration = 1;
	m_body->velocityIteration = 1;
	m_body->isContinousDetection = true;


	m_colliderObj = CreateGameObjectToChild(transform);
	m_colliderObj->transform->scale = Vec3::one() * 0.5f;
	m_collider = m_colliderObj->AddComponent<SphereCollider>();
	m_collider->layerIndex = (uint8_t)PhysicsLayers::Projectile;
	m_collider->restitutionCombineMode = PhysicsCombineMode::Average;
	m_collider->restitution = 0.5f;
	m_collider->friction = 0.5f;
	m_collider->SetIgnoreLayerBits(1 << (uint32_t)PhysicsLayers::Player);
	m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &WarmechMissile::OnCollisionEnter);

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localScale = Vec3::one() * 0.25f;


	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();

	//{	// For debug
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	m_debugRenderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}
}

void WarmechMissile::Update()
{

	m_selfDestroyCounter -= Time::DeltaTime();

	if (m_selfDestroyCounter <= 0)
	{
		gameObject->Destroy();
	}

	m_animator->SetDefaultAnimation(m_animator->GetSpriteAnimation(SPRITE_WARMECH::MissileBullet), true);

	Vec3 playerPos = Player::GetInstance()->transform->position;
	Vec3 missilePos = transform->position;


	if (m_initialdir)
	{
		forward = playerPos - missilePos;
		forward.Normalize();
		transform->forward = forward;
		m_initialdir = false;
	}


	if (m_groundCollision)
	{
		m_selfExplosionCounter -= Time::DeltaTime();
	}
	else
	{
		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		Vec3 velocity = Quat::AxisAngle(right, -22.5f) * forward * m_moveSpeed;

		transform->position += velocity * 0.03f;
	}

	Rebound();

	if (m_selfExplosionCounter <= 0)
	{
		Explosion();

		gameObject->Destroy();
	}

}

void WarmechMissile::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}

void WarmechMissile::OnCollisionEnter(const CollisionEnter& collider)
{
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
	{
		if (m_rebound)
		{
			m_reboudcount = 3;
			m_rebound = false;
		}

		m_groundCollision = true;
	}
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		Explosion();

		gameObject->Destroy();
	}
}

void WarmechMissile::Explosion()
{
	{
		auto obj = CreateGameObject();
		obj->transform->position = transform->position + (-transform->right);
		obj->AddComponent<WarmechExplosion>();

	}
	{
		auto obj = CreateGameObject();
		obj->transform->position = transform->position + transform->right;
		obj->AddComponent<WarmechExplosion>();

	}
	{
		auto obj = CreateGameObject();
		obj->transform->position = transform->position + transform->up;
		obj->AddComponent<WarmechExplosion>();

	}
}

void WarmechMissile::Rebound()
{

	if ((m_reboudcount > 0) && m_groundCollision)
	{
		--m_reboudcount;

		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		Vec3 velocity = Quat::AxisAngle(right, -65) * forward * 2.f;

		transform->position += velocity * 0.03f;

	}


}
