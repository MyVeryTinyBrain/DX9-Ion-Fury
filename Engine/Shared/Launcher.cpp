#include "shared_stdafx.h"
#include "Launcher.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"
#include "LauncherAnimator.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "PhysicsLayers.h"
#include "BulletProof.h"
#include "Monster.h"
#include "OrthoEffect.h"
#include "LauncherGranade.h"

void Launcher::Awake()
{
	Weapon::Awake();

	// ������ �� ����
	m_rightHandObj = CreateGameObjectToChild(transform);
	m_rightHandRenderer = m_rightHandObj->AddComponent<UserMeshRenderer>();
	m_rightHandRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_rightHandRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_rightHandRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_rightHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerRightHand);

	// �ִϸ����� ���� �� �̺�Ʈ�Լ� ���
	m_animator = m_rightHandObj->AddComponent<LauncherAnimator>();
	m_animator->OnReloaded += Function<void()>(this, &Launcher::OnReloaded);
	m_animator->OnSkinChanged += Function<void()>(this, &Launcher::OnSkinChanged);

	// ����� ũ��� �׿� ���� ��ġ ����
	m_rightHandObj->transform->localScale = m_rightHandLocalScale;
	m_rightHandObj->transform->localPosition = m_rightHandLocalPosition;

	m_currentAmmo = &m_shotgunAmmo;
}

void Launcher::Update()
{
	Weapon::Update();

	if (m_currentAmmo->loadedAmmo == 0)
	{
		TryReload();
	}

	if (m_animator->IsPlayingShoot())
	{
		const float t = m_animator->GetPercent();
		float func = sinf(PI * powf(t, 0.5f)) * 0.2f;
		m_rightHandObj->transform->localPosition = m_rightHandLocalPosition + Vec2(func, -func * 1.5f);
	}
	else
	{
		m_rightHandObj->transform->localPosition = m_rightHandLocalPosition;
	}
}

void Launcher::OnDestroy()
{
	Weapon::OnDestroy();

	m_animator->OnReloaded -= Function<void()>(this, &Launcher::OnReloaded);
	m_animator->OnSkinChanged -= Function<void()>(this, &Launcher::OnSkinChanged);
}

void Launcher::OnChanged()
{
	m_animator->PlayIdle();
}

void Launcher::OnPutIn()
{
}

void Launcher::OnAttackInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing && 
		m_animator->IsPlayingIdle() && 
		m_currentAmmo->loadedAmmo > 0)
	{
		m_animator->PlayShoot();

		MakeFireEffect();

		Attack();

		float randomAngle = float(rand() % 50 - 25) + 90.0f;
		Player::GetInstance()->controller->fpsCamera->MakeRecoil(Vec2::Direction(randomAngle) * 6.0f, 0.2f, 6.0f);

		--m_currentAmmo->loadedAmmo;
	}
}

void Launcher::OnSubInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		bool isIdle = m_animator->IsPlayingIdle();
		bool isEnfOfPullPump = m_animator->IsPlayingPullPump() && m_animator->GetPercent() > 0.8f;
		bool isHalfReloading = m_animator->IsPlayingReload() && m_animator->GetPercent() < 0.4f;

		if (!isIdle && !isEnfOfPullPump && !isHalfReloading)
		{
			return;
		}

		float elapsed = m_animator->GetElapsedTime();

		if (m_mode == Mode::Shotgun)
		{
			m_animator->PlayChangeToYellow();

			if (isHalfReloading)
			{
				m_animator->SetElapsedTime(elapsed);
			}
		}
		else
		{
			m_animator->PlayChangeToRed();

			if (isHalfReloading)
			{
				m_animator->SetElapsedTime(elapsed);
			}
		}
	}
}

void Launcher::OnReloadInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		TryReload();
	}
}

AmmoTypes Launcher::GetAmmoType0() const
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			return AmmoTypes::Shotgun;
			break;
		case Mode::Launcher:
			return AmmoTypes::Launcher;
			break;
	}

	return AmmoTypes::None;
}

AmmoTypes Launcher::GetAmmoType1() const
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			return AmmoTypes::Launcher;
			break;
		case Mode::Launcher:
			return AmmoTypes::Shotgun;
			break;
	}

	return AmmoTypes::None;
}

unsigned int Launcher::GetTotalAmmo0() const
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			return m_shotgunAmmo.totalAmmo;
			break;
		case Mode::Launcher:
			return m_launcherAmmo.totalAmmo;
			break;
	}

	return 0;
}

unsigned int Launcher::GetTotalAmmo1() const
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			return m_launcherAmmo.totalAmmo;
			break;
		case Mode::Launcher:
			return m_shotgunAmmo.totalAmmo;
			break;
	}

	return 0;
}

unsigned int Launcher::GetLoadedAmmo0() const
{
	return m_currentAmmo->loadedAmmo;
}

unsigned int Launcher::GetLoadedAmmo1() const
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			return m_launcherAmmo.loadedAmmo;
			break;
		case Mode::Launcher:
			return m_shotgunAmmo.loadedAmmo;
			break;
	}

	return 0;
}

bool Launcher::GetLoadedAmmo0State() const
{
	return true;
}

bool Launcher::GetLoadedAmmo1State() const
{
	return true;
}

void Launcher::AddAmmo(AmmoTypes ammo, unsigned int count)
{
	switch (ammo)
	{
		case AmmoTypes::Shotgun:
			{
				m_shotgunAmmo.totalAmmo += count;

				if (m_shotgunAmmo.totalAmmo > 999)
				{
					m_shotgunAmmo.totalAmmo = 999;
				}
			}
			break;
		case AmmoTypes::Launcher:
			{
				m_launcherAmmo.totalAmmo += count;

				if (m_launcherAmmo.totalAmmo > 999)
				{
					m_launcherAmmo.totalAmmo = 999;
				}
			}
			break;
	}
}

void Launcher::OnReloaded()
{
	int emptyAmmos = (int)Abs(m_currentAmmo->ammoLoadMax - m_currentAmmo->loadedAmmo);
	int reloadableAmmos = (int)Clamp(emptyAmmos, 0, m_currentAmmo->totalAmmo);
	m_currentAmmo->loadedAmmo += reloadableAmmos;
	m_currentAmmo->totalAmmo -= reloadableAmmos;
}

void Launcher::OnSkinChanged()
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			m_mode = Mode::Launcher;
			m_currentAmmo = &m_launcherAmmo;
			break;
		case Mode::Launcher:
			m_mode = Mode::Shotgun;
			m_currentAmmo = &m_shotgunAmmo;
			break;
	}
}

void Launcher::TryReload()
{
	if (m_animator->IsPlayingIdle() &&
		m_currentAmmo->totalAmmo > 0 &&
		m_currentAmmo->loadedAmmo < m_currentAmmo->ammoLoadMax)
	{
		m_animator->PlayReload();
	}
}

void Launcher::Attack()
{
	switch (m_mode)
	{
		case Mode::Shotgun:
			AttackWithShotgun();
			break;
		case Mode::Launcher:
			AttackWithLauncher();
			break;
	}
}

void Launcher::AttackWithShotgun()
{
	for (int i = 0; i < m_numShotgunBullet; ++i)
	{
		ShotgunShootOnce();
	}
}

void Launcher::AttackWithLauncher()
{
	LauncherShootOnce();
}

void Launcher::ShotgunShootOnce()
{
	RaycastHit hit;
	PhysicsRay ray;
	ray.distance = FLT_MAX;
	ray.point = Player::GetInstance()->perspectiveCamera->transform->position;

	float randomXAngle = float(rand() % m_shotgunSpreadAngleRange - m_shotgunSpreadAngleRange / 2);
	float randomYAngle = float(rand() % m_shotgunSpreadAngleRange - m_shotgunSpreadAngleRange / 2);
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
				DamageParameters params;
				params.monsterHitCollider = hit.collider;
				params.damageType = MonsterDamageType::Bullet;
				params.damage = 2.5f;
				params.force = ray.direction * 10;
				params.includeDamageDirection = true;
				params.damageDirection = ray.direction;
				params.includeAttackBeginPoint = true;
				params.attackBeginPoint = ray.point;
				params.includeMonsterHitWorldPoint = true;
				params.monsterHitWorldPoint = hit.point;

				monster->TakeDamage(params);
			}
		}
	}
}

void Launcher::LauncherShootOnce()
{
	Transform* cameraTransform = Player::GetInstance()->perspectiveCamera->transform;

	GameObject* granadeObj = CreateGameObject();
	granadeObj->transform->position = cameraTransform->position + cameraTransform->forward * 0.5f;

	LauncherGranade* granade = granadeObj->AddComponent<LauncherGranade>();
	granade->rigidbody->isContinousDetection = true;
	granade->rigidbody->velocity = cameraTransform->rotation * Quat::AxisAngle(Vec3::right(), -2.5f) * Vec3::forawrd() * 25;
}

void Launcher::MakeFireEffect()
{
	auto effectObj = CreateGameObjectToChild(m_rightHandObj->transform);
	effectObj->transform->localPosition = Vec2(0.23f, -0.2f);
	effectObj->transform->localEulerAngle = Vec3(0, 0, -10);
	effectObj->transform->localScale = Vec2(0.25f, 0.25f);
	auto effect = effectObj->AddComponent<OrthoEffect>();
	effect->AddTexture(L"../SharedResource/Texture/launcher_effect/launcher_fire0.png");
	effect->AddTexture(L"../SharedResource/Texture/launcher_effect/launcher_fire1.png");
	effect->AddTexture(L"../SharedResource/Texture/launcher_effect/launcher_fire2.png");
	effect->SetInterval(0.03f);
}