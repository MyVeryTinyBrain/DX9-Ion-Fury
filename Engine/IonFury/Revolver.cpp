#include "stdafx.h"
#include "Revolver.h"
#include "RevolverAnimator.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "FPSOrthoCamera.h"
#include "OrthoEffect.h"
#include "PhysicsLayers.h"
#include "Monster.h"
#include "BulletProof.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"

void Revolver::Awake()
{
	Weapon::Awake();

	m_animator = m_rightHandObj->AddComponent<RevolverAnimator>();
	m_animator->OnReloaded += Function<void()>(this, &Revolver::OnReloaded);

	// ¿À¸¥ÂÊ ¼Õ

	m_rightHandObj->transform->localPosition = Vec2(0.1f, -0.2f);

	m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);

	m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);

	m_animator->PlayDefaultAnimation();

	m_totalAmmo = 100;

	m_loadedAmmo = 6;

	m_ammoLoadMax = 6;

	// ¿ÞÂÊ ¼Õ

	m_leftHandObj = CreateGameObjectToChild(transform);
	m_leftHandChildObj = CreateGameObjectToChild(m_leftHandObj->transform);
	m_leftHandRenderer = m_leftHandChildObj->AddComponent<UserMeshRenderer>();
	m_leftHandRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_leftHandRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_leftHandRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_leftHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerLeftHand);
	m_leftHandObj->activeSelf = false;

	m_leftHandRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/revolver/revolver_lefthand.png"));

	m_leftHandObj->transform->localPosition = m_leftHandHideLocalPosition;

	m_leftHandChildObj->transform->localPosition = Vec2::zero();

	m_leftHandLocalPositionTarget = m_leftHandHideLocalPosition;

	m_leftHandObj->activeSelf = true;
}

void Revolver::Update()
{
	Weapon::Update();

	if (m_loadedAmmo == 0)
	{
		TryReload();
	}

	if (m_animator->IsPlayingReloadPutin())
	{
		m_rightHandLocalPositionTarget = Vec2(0.0f, -1.0f);
		m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 45);
	}
	else
	{
		m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);
		m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);
	}

	if (m_animator->IsPlayingFastShoot())
	{
		const float t = m_animator->GetPercent();
		float func = (-sinf(TAU * t - PI * 0.5f) - 1.0f) * 0.5f;
		m_leftHandChildObj->transform->localPosition = Vec2(-func * 0.15f, func * 0.25f);
	}
	else
	{
		m_leftHandChildObj->transform->localPosition = Vec2::zero();
	}

	m_rightHandObj->transform->localPosition = Vec2::Lerp(m_rightHandObj->transform->localPosition, m_rightHandLocalPositionTarget, Time::DeltaTime() * 10.0f);
	m_rightHandObj->transform->localEulerAngle = Vec3::Lerp(m_rightHandObj->transform->localEulerAngle, m_rightHandLocalEulerAngleTarget, Time::DeltaTime() * 10.0f);

	m_leftHandObj->transform->localPosition = Vec2::Lerp(m_leftHandObj->transform->localPosition, m_leftHandLocalPositionTarget, Time::DeltaTime() * 30.0f);
}

void Revolver::OnDestroy()
{
	m_animator->OnReloaded -= Function<void()>(this, &Revolver::OnReloaded);
}

void Revolver::OnChanged()
{
	m_rightHandObj->transform->localPosition = Vec2(0.1f, -0.2f);

	m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);

	m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);

	m_leftHandObj->activeSelf = true;

	m_animator->PlayDefaultAnimation();

	// ¿ÞÂÊ ¼Õ

	m_leftHandRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/revolver/revolver_lefthand.png"));

	m_leftHandObj->transform->localPosition = m_leftHandHideLocalPosition;

	m_leftHandChildObj->transform->localPosition = Vec2::zero();

	m_leftHandLocalPositionTarget = m_leftHandHideLocalPosition;

	m_leftHandObj->activeSelf = true;
}

void Revolver::OnAttackInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		if (m_animator->IsPlayingIdle() &&
			m_loadedAmmo > 0)
		{
			if (Vec2::Distance(m_leftHandObj->transform->localPosition, m_leftHandShowLocalPosition) <= 0.1f)
			{
				m_animator->PlayFastShoot();
			}
			else
			{
				m_animator->PlayShoot();
			}

			float randomAngle = float(rand() % 60 - 30) + 90.0f;
			Player::GetInstance()->controller->fpsCamera->MakeRecoil(Vec2::Direction(randomAngle) * 2.0f, 0.25f, 4.0f);

			auto effectObj = CreateGameObjectToChild(m_rightHandObj->transform);
			effectObj->transform->localPosition = Vec2(0.1f, 0.05f);
			effectObj->transform->localScale = Vec2::one() * 0.5f;
			auto effect = effectObj->AddComponent<OrthoEffect>();
			effect->SetSpeed(1.5f);
			effect->AddTexture(L"../SharedResource/Texture/revolver/revolver_effect0.png");
			effect->AddTexture(L"../SharedResource/Texture/revolver/revolver_effect1.png");
			effect->AddTexture(L"../SharedResource/Texture/revolver/revolver_effect2.png");

			Attack();

			--m_loadedAmmo;
		}
	}
}

void Revolver::OnSubInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing &&
		!m_animator->IsPlayingReload())
	{
		m_leftHandLocalPositionTarget = m_leftHandShowLocalPosition;
	}
	else
	{
		m_leftHandLocalPositionTarget = m_leftHandHideLocalPosition;
	}
}

void Revolver::OnReloadInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		TryReload();
	}
}

void Revolver::OnReloaded()
{
	int emptyAmmos = (int)Abs(m_ammoLoadMax - m_loadedAmmo);
	int reloadableAmmos = (int)Clamp(emptyAmmos, 0, m_totalAmmo);
	m_loadedAmmo += reloadableAmmos;
	m_totalAmmo -= reloadableAmmos;
}

void Revolver::TryReload()
{
	if (m_animator->IsPlayingIdle() &&
		m_totalAmmo > 0)
	{
		m_animator->PlayReload();
	}
}

void Revolver::Attack()
{
	RaycastHit hit;
	PhysicsRay ray;
	ray.direction = Player::GetInstance()->perspectiveCamera->transform->forward;
	ray.distance = FLT_MAX;
	ray.point = Player::GetInstance()->perspectiveCamera->transform->position;

	if (Vec2::Distance(m_leftHandObj->transform->localPosition, m_leftHandShowLocalPosition) <= 0.1f)
	{
		float randomXAngle = float(rand() % m_rapidFireRecoilAngleRange - m_rapidFireRecoilAngleRange / 2);
		float randomYAngle = float(rand() % m_rapidFireRecoilAngleRange - m_rapidFireRecoilAngleRange / 2);
		ray.direction = Quat::FromEuler(randomXAngle, randomYAngle, 0) * ray.direction;
	}

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
