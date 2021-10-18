#include "stdafx.h"
#include "WarmechMissile.h"
#include "WarmechSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "GranadeTrail.h"


void WarmechMissile::Awake()
{
	auto trailObj = CreateGameObjectToChild(transform);
	GranadeTrail* trail = trailObj->AddComponent<GranadeTrail>();


	m_moveSpeed = 3.0f;


	m_body = gameObject->AddComponent<Rigidbody>();
	m_body->SetRotationLockAxis(PhysicsAxis::All, true);

	m_body->mass = 0.01f;
	m_body->interpolate = Interpolate::Extrapolate;

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

void WarmechMissile::FixedUpdate()
{
	Collider* collider = Physics::OverlapSphere(
		transform->position,
		m_radius,
		(1 << (PxU32)PhysicsLayers::Terrain || 1 << (PxU32)PhysicsLayers::Player),
		PhysicsQueryType::Collider);

	if (collider)
	{
		if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
		
		}
		else if (collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{

		}
	}
}

void WarmechMissile::Update()
{
	
	m_animator->SetDefaultAnimation(m_animator->GetMissileBullet(), true);


	Vec3 playerPos = Player::GetInstance()->transform->position;
	Vec3 missilePos = transform->position;


	if (m_initialdir)
	{
		forward = playerPos - missilePos;
		forward.Normalize();
		transform->forward = forward;
		m_initialdir = false;
	}

	Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

	Vec3 velocity = Quat::AxisAngle(right, -22.5f) * forward * m_moveSpeed;

	transform->position += velocity * 0.03f;



}

void WarmechMissile::LateUpdate()
{
}

void WarmechMissile::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
