#include "stdafx.h"
#include "Chaingun.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"
#include "ChaingunGunpartAnimator.h"
#include "ChaingunAmmopartAnimator.h"
#include "OrthoEffect.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "PhysicsLayers.h"
#include "BulletProof.h"
#include "Monster.h"

void Chaingun::Awake()
{
	Weapon::Awake();

	// ��ü ������Ʈ ����
	m_bodyObj = CreateGameObjectToChild(transform);

	// �ѿ� ������Ʈ ����
	m_gunObj = CreateGameObjectToChild(m_bodyObj->transform);

	// �Ѿ��� ������Ʈ ����
	m_ammoObj = CreateGameObjectToChild(m_bodyObj->transform);

	m_bodyRenderer = m_bodyObj->AddComponent<UserMeshRenderer>();
	m_bodyRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_bodyRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_bodyRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_bodyRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerWeaponOverlay0);
	m_bodyRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/chaingun/body.png"));

	m_gunRenderer = m_gunObj->AddComponent<UserMeshRenderer>();
	m_gunRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_gunRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_gunRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_gunRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerWeaponOverlay1);

	m_ammoRenderer = m_ammoObj->AddComponent<UserMeshRenderer>();
	m_ammoRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_ammoRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_ammoRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_ammoRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerWeaponOverlay2);

	// �ִϸ����� ����
	m_gunAnimator = m_gunObj->AddComponent<ChaingunGunpartAnimator>();
	m_gunAnimator->OnRotatedBarrel += Function<void()>(this, &Chaingun::OnRotateBarrel);

	m_ammoAnimator = m_ammoObj->AddComponent<ChaingunAmmopartAnimator>();

	// ����� ũ��� �׿� ���� ��ġ ����
	m_bodyObj->transform->localScale = Vec2(2, 2);
	m_bodyObj->transform->localPosition = Vec2(-0.25f, 0.4f);
}

void Chaingun::Update()
{
	Weapon::Update();
}

void Chaingun::OnDestroy()
{
	Weapon::OnDestroy();

	m_gunAnimator->OnRotatedBarrel -= Function<void()>(this, &Chaingun::OnRotateBarrel);
}

void Chaingun::OnChanged()
{
	m_gunAnimator->speed = 0;

	m_ammoAnimator->PlayIdle();

	m_hasAttackInput = false;
}

void Chaingun::OnPutIn()
{
	m_hasAttackInput = false;
}

void Chaingun::OnAttackInput(InputType inputType)
{
	m_hasAttackInput = inputType == InputType::KeyPressing;
}

void Chaingun::OnSubInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		m_gunAnimator->speed += Time::DeltaTime() * m_spinFactor;
		m_gunAnimator->speed = Clamp(m_gunAnimator->speed, 0, m_maxSpinSpeed);
	}
	else
	{
		m_gunAnimator->speed -= Time::DeltaTime() * m_spinFactor;
		m_gunAnimator->speed = Clamp(m_gunAnimator->speed, 0, m_maxSpinSpeed);
	}
}

void Chaingun::OnReloadInput(InputType inputType)
{
}

void Chaingun::OnRotateBarrel()
{
	if (m_ammo <= 0)
	{
		return;
	}

	if (m_hasAttackInput)
	{
		m_ammoAnimator->PlayAnim();

		MakeRightFireEffect();

		Attack();

		float randomAngle = float(rand() % 80 - 40) + 90.0f;
		Player::GetInstance()->controller->fpsCamera->MakeRecoil(Vec2::Direction(randomAngle) * 0.4f, 0.3f, 6.0f);

		--m_ammo;
	}
}

void Chaingun::MakeRightFireEffect()
{
	auto effectObj = CreateGameObjectToChild(m_gunObj->transform);
	effectObj->transform->localPosition = Vec2(0.17f, -0.3f);
	effectObj->transform->localScale = Vec2(0.2f, 0.2f);
	effectObj->transform->localEulerAngle = Vec3(0, 0, float(rand() % 360));
	auto effect = effectObj->AddComponent<OrthoEffect>();
	effect->AddTexture(L"../SharedResource/Texture/explosion1/3.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/4.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/5.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/6.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/7.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/8.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/9.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/10.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/11.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/12.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion1/13.png");
	effect->SetInterval(0.01f);
}

void Chaingun::Attack()
{
	RaycastHit hit;
	PhysicsRay ray;
	ray.direction = Player::GetInstance()->perspectiveCamera->transform->forward;
	ray.distance = FLT_MAX;
	ray.point = Player::GetInstance()->perspectiveCamera->transform->position;

	float randomXAngle = float(rand() % m_angleRange - m_angleRange / 2);
	float randomYAngle = float(rand() % m_angleRange - m_angleRange / 2);
	ray.direction = Player::GetInstance()->perspectiveCamera->transform->rotation * Quat::FromEuler(randomXAngle, randomYAngle, 0) * Vec3::forawrd();

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster)))
	{
		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
			auto bulletProofObj = CreateGameObject();
			auto bulletProof = bulletProofObj->AddComponent<BulletProof>();
			bulletProof->InitializeBulletProof(hit.point, hit.normal);
		}
		else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
		{
			auto monster = hit.collider->rigidbody->gameObject->GetComponent<Monster>();
			if (monster)
			{
				monster->TakeDamage(hit.collider, MonsterDamageType::Bullet, 5, ray.direction * 10);
			}
		}
	}
}
