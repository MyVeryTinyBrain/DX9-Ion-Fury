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

void Revolver::Awake()
{
	Weapon::Awake();

	m_animator = m_rightHandObj->AddComponent<RevolverAnimator>();
	m_animator->OnReloaded += Function<void()>(this, &Revolver::OnReloaded);

	m_rightHandObj->transform->localPosition = Vec2(0.1f, -0.2f);

	m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);

	m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);

	m_leftHandObj->activeSelf = false;

	m_animator->PlayDefaultAnimation();

	m_totalAmmo = 60;

	m_loadedAmmo = 6;

	m_ammoLoadMax = 6;
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

	m_rightHandObj->transform->localPosition = Vec2::Lerp(m_rightHandObj->transform->localPosition, m_rightHandLocalPositionTarget, Time::DeltaTime() * 10.0f);
	m_rightHandObj->transform->localEulerAngle = Vec3::Lerp(m_rightHandObj->transform->localEulerAngle, m_rightHandLocalEulerAngleTarget, Time::DeltaTime() * 10.0f);
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

	m_leftHandObj->activeSelf = false;

	m_animator->PlayDefaultAnimation();
}

void Revolver::OnAttackInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		if (m_animator->IsPlayingIdle() &&
			m_loadedAmmo > 0)
		{
			m_animator->PlayShoot();

			float randomAngle = float(rand() % 40 - 20) + 90.0f;
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
