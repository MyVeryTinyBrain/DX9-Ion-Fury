#include "shared_stdafx.h"
#include "SMG.h"
#include "SMGAnimator.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"
#include "OrthoEffect.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "Monster.h"
#include "PhysicsLayers.h"
#include "BulletProof.h"

void SMG::Awake()
{
	Weapon::Awake();

	// 손 부모 생성
	m_hansParentObj = CreateGameObjectToChild(transform);
	m_hansParentObj->transform->localPosition = Vec2(0, -0.15f);

	// 오른쪽 손 생성
	m_rightHandObj = CreateGameObjectToChild(m_hansParentObj->transform);
	m_rightHandRenderer = m_rightHandObj->AddComponent<UserMeshRenderer>();
	m_rightHandRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_rightHandRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_rightHandRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_rightHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerRightHand);

	// 애니메이터 부착 및 이벤트함수 등록
	m_rightHandAnimator = m_rightHandObj->AddComponent<SMGAnimator>();
	m_rightHandAnimator->OnReloaded += Function<void()>(this, &SMG::OnRightReloaded);

	// 왼쪽 손 메쉬 생성
	m_leftHandQuad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_leftHandQuad->uvScale = Vec2(-1, 1);

	// 왼쪽 손 생성
	m_leftHandObj = CreateGameObjectToChild(m_hansParentObj->transform);

	m_leftHandChild = CreateGameObjectToChild(m_leftHandObj->transform);

	m_leftHandRenderer = m_leftHandChild->AddComponent<UserMeshRenderer>();
	m_leftHandRenderer->userMesh = m_leftHandQuad;
	m_leftHandRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_leftHandRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_leftHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerLeftHand);

	// 애니메이터 부착 및 이벤트함수 등록
	m_leftHandAnimator = m_leftHandChild->AddComponent<SMGAnimator>();
	m_leftHandAnimator->OnReloaded += Function<void()>(this, &SMG::OnLeftReloaded);
	m_leftHandAnimator->OnPlayedPutin += Function<void()>(this, &SMG::OnPlayedLeftPutin);
	m_leftHandAnimator->OnPlayPullout += Function<void()>(this, &SMG::OnPlayLeftPullout);

	// 왼쪽 손은 처음에 비활성화입니다.
	m_leftHandObj->activeSelf = false;
}

void SMG::Update()
{
	Weapon::Update();

	if (!m_leftHandObj->activeInTree &&
		m_rightAmmo == 0)
	{
		TryReload();
	}

	if (m_leftHandObj->activeInTree &&
		m_leftAmmo == 0 && 
		m_rightAmmo == 0)
	{
		TryReload();
	}
}

void SMG::LateUpdate()
{
	Weapon::LateUpdate();

	if (m_leftHandAnimator->IsPlayingPutin())
	{
		m_leftHandChild->transform->localPosition = Vec2::Lerp(m_leftHandChild->transform->localPosition, Vec2(0, -1), Time::DeltaTime() * 5.0f);
	}
	else if (m_leftHandObj->activeInTree && m_rightHandAnimator->IsPlayingReload())
	{
		m_leftHandChild->transform->localPosition = Vec2::Lerp(m_leftHandChild->transform->localPosition, Vec2(0, -1), Time::DeltaTime() * 5.0f);
	}
	else
	{
		m_leftHandChild->transform->localPosition = Vec2::Lerp(m_leftHandChild->transform->localPosition, Vec2(0, 0), Time::DeltaTime() * 25.0f);
	}

	if (m_leftHandAnimator->IsPlayingReload())
	{
		m_rightHandObj->transform->localPosition = Vec2::Lerp(m_rightHandObj->transform->localPosition, Vec2(0, -1), Time::DeltaTime() * 5.0f);
	}
	else
	{
		m_rightHandObj->transform->localPosition = Vec2::Lerp(m_rightHandObj->transform->localPosition, Vec2(0, 0), Time::DeltaTime() * 25.0f);
	}
}

void SMG::OnDestroy()
{
	Weapon::OnDestroy();

	m_leftHandQuad->ReleaseUnmanaged();
}

void SMG::OnChanged()
{
	m_rightHandAnimator->PlayIdle();
	m_leftHandAnimator->PlayIdle();
}

void SMG::OnPutIn()
{
}

void SMG::OnAttackInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		if (m_leftHandObj->activeInTree && 
			!m_leftHandAnimator->IsPlayingIdle())
		{
			return;
		}
		if (!m_rightHandAnimator->IsPlayingIdle())
		{
			return;
		}

		if (m_rightAmmo <= 0 &&
			m_leftHandObj->activeInTree &&
			m_leftAmmo <= 0)
		{
			return;
		}

		if (m_rightAmmo <= 0 &&
			!m_leftHandObj->activeInTree)
		{
			return;
		}

		float recoilFactor = 1.0f;

		if (m_leftHandObj->activeInTree &&
			m_leftAmmo > 0 &&
			m_rightAmmo > 0)
		{
			recoilFactor = 1.80f;
		}

		if (m_leftHandObj->activeInTree &&
			m_leftAmmo > 0)
		{
			m_leftHandAnimator->PlayFire();

			MakeLeftFireEffect();

			int angleRange = 0;

			if (m_rightAmmo > 0)
			{
				angleRange = 4;
			}

			AttackOnce(angleRange);

			--m_leftAmmo;
		}

		if(m_rightAmmo > 0)
		{
			m_rightHandAnimator->PlayFire();

			MakeRightFireEffect();

			AttackOnce(0);

			--m_rightAmmo;
		}

		float randomAngle = float(rand() % 140 - 70) + 90.0f;
		Player::GetInstance()->controller->fpsCamera->MakeRecoil(Vec2::Direction(randomAngle) * 0.75f * recoilFactor, 0.3f, 6.0f);
	}
}

void SMG::OnSubInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		if (!m_leftHandAnimator->IsPlayingIdle())
		{
			return;
		}
		if (!m_rightHandAnimator->IsPlayingIdle())
		{
			return;
		}

		if (m_leftHandObj->activeInTree)
		{
			m_leftHandAnimator->PlayPutin();
		}
		else
		{
			m_leftHandAnimator->PlayPullout();
		}
	}
}

void SMG::OnReloadInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		TryReload();
	}
}

AmmoTypes SMG::GetAmmoType0() const
{
	return AmmoTypes::SMG;
}

AmmoTypes SMG::GetAmmoType1() const
{
	return AmmoTypes::None;
}

unsigned int SMG::GetTotalAmmo0() const
{
	return m_totalAmmo;
}

unsigned int SMG::GetTotalAmmo1() const
{
	return 0;
}

unsigned int SMG::GetLoadedAmmo0() const
{
	return m_rightAmmo;
}

unsigned int SMG::GetLoadedAmmo1() const
{
	return m_leftAmmo;
}

bool SMG::GetLoadedAmmo0State() const
{
	return true;
}

bool SMG::GetLoadedAmmo1State() const
{
	return m_leftHandObj->activeInTree;
}

void SMG::AddAmmo(AmmoTypes ammo, unsigned int count)
{
	m_totalAmmo += count;

	if (m_totalAmmo > 999)
	{
		m_totalAmmo = 999;
	}
}

void SMG::OnPlayedLeftPutin()
{
	m_leftHandObj->activeSelf = false;
	m_leftHandChild->transform->localPosition = Vec2(0, 0);
}

void SMG::OnPlayLeftPullout()
{
	m_leftHandObj->activeSelf = true;
	m_leftHandChild->transform->localPosition = Vec2(0, -1);
}

void SMG::OnRightReloaded()
{
	int emptyAmmos = (int)Abs(float(m_ammoLoadMax - m_rightAmmo));
	int reloadableAmmos = (int)Clamp(emptyAmmos, 0, float(m_totalAmmo));
	m_rightAmmo += reloadableAmmos;
	m_totalAmmo -= reloadableAmmos;

	TryReload();
}

void SMG::OnLeftReloaded()
{
	int emptyAmmos = (int)Abs(float(m_ammoLoadMax - m_leftAmmo));
	int reloadableAmmos = (int)Clamp(emptyAmmos, 0, float(m_totalAmmo));
	m_leftAmmo += reloadableAmmos;
	m_totalAmmo -= reloadableAmmos;

	TryReload();
}

void SMG::TryReload()
{
	if (!m_rightHandAnimator->IsPlayingIdle())
	{
		return;
	}

	if (m_leftHandObj->activeInTree &&
		!m_leftHandAnimator->IsPlayingIdle())
	{
		return;
	}

	if (m_totalAmmo <= 0)
	{
		return;
	}

	if (m_rightHandAnimator->IsPlayingIdle() &&
		m_rightAmmo < m_ammoLoadMax)
	{
		m_rightHandAnimator->PlayReload();
		return;
	}

	if (m_leftHandObj->activeInTree &&
		m_leftHandAnimator->IsPlayingIdle() &&
		m_leftAmmo < m_ammoLoadMax)
	{
		m_leftHandAnimator->PlayReload();
		return;
	}
}

void SMG::AttackOnce(int recoilAngleRange)
{
	RaycastHit hit;
	PhysicsRay ray;
	ray.direction = Player::GetInstance()->perspectiveCamera->transform->forward;
	ray.distance = FLT_MAX;
	ray.point = Player::GetInstance()->perspectiveCamera->transform->position;

	float randomXAngle = 0;
	float randomYAngle = 0;
	if (recoilAngleRange > 0)
	{
		randomXAngle = float(rand() % 2);
		randomYAngle = float(rand() % 2);
		if (randomXAngle == 1) randomXAngle = -float(recoilAngleRange);
		if (randomXAngle == 0) randomXAngle = +float(recoilAngleRange);
		if (randomYAngle == 1) randomYAngle = -float(recoilAngleRange);
		if (randomYAngle == 0) randomYAngle = +float(recoilAngleRange);
	}
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

void SMG::MakeRightFireEffect()
{
	auto effectObj = CreateGameObjectToChild(m_rightHandObj->transform);
	effectObj->transform->localPosition = Vec2(0.225f, -0.06f);
	effectObj->transform->localScale = Vec2(0.4f, 0.4f);
	effectObj->transform->localEulerAngle = Vec3(0, 0, float(rand() % 60 - 30));
	auto effect = effectObj->AddComponent<OrthoEffect>();
	effect->AddTexture(L"../SharedResource/Texture/smg/effect_right0.png");
	effect->AddTexture(L"../SharedResource/Texture/smg/effect_right1.png");
	effect->AddTexture(L"../SharedResource/Texture/smg/effect_right2.png");
	effect->SetInterval(0.02f);
}

void SMG::MakeLeftFireEffect()
{
	auto effectObj = CreateGameObjectToChild(m_leftHandObj->transform);
	effectObj->transform->localPosition = Vec2(-0.225f, -0.06f);
	effectObj->transform->localScale = Vec2(0.4f, 0.4f);
	effectObj->transform->localEulerAngle = Vec3(0, 0, float(rand() % 60 - 30));
	auto effect = effectObj->AddComponent<OrthoEffect>();
	effect->AddTexture(L"../SharedResource/Texture/smg/effect_left0.png");
	effect->AddTexture(L"../SharedResource/Texture/smg/effect_left1.png");
	effect->AddTexture(L"../SharedResource/Texture/smg/effect_left2.png");
	effect->SetInterval(0.02f);
}

void SMG::DebugAmmos()
{
	char buffer[256];
	sprintf_s(buffer, "left(%d), right(%d), total(%d)", m_leftAmmo, m_rightAmmo, m_totalAmmo);
	cout << buffer << endl;
}
