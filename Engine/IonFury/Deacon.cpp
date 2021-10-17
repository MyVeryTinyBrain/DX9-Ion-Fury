#include "stdafx.h"
#include "Deacon.h"
#include "DeaconSpriteAnimator.h"
#include "PhysicsInitialize.h"
#include "Player.h"
#include "BloodEffect.h"

void Deacon::Awake()
{
    Monster::Awake();

    m_hp = 5;
    m_moveSpeed = 2.f;

    m_body->mass = 1.f;
    //질량

    m_body->interpolate = true;
    // 보간

    m_body->useGravity = false;
    // 중력

    m_body->sleepThresholder = 1.f;
    //절전 모드로 전환될 수 있습니다. Rigidbody가 잠자기 상태일 때 프레임마다 업데이트되지 않으므로 리소스 집약적이지 않습니다. 리지드바디의 운동 에너지를 질량으로 나눈 값이 이 임계값보다 낮으면 수면 후보입니다.

    m_rendererObj->transform->scale = Vec3::one() * 10.0f;

    m_rendererObj->transform->localPosition = Vec3(0, -0.5f, 0);
  
    m_renderer->freezeX = false;
    m_renderer->freezeZ = false;
    //빌보드 

    m_animator = m_rendererChildObj->AddComponent<DeaconSpriteAnimator>();

}

void Deacon::FixedUpdate()
{
    //물리 업데이트 
    Monster::FixedUpdate();

    if (m_isDead)
    {
        return;
    }

    if (!m_hasTargetCoord)
    {
        Vec3 targetCoord = Player::GetInstance()->transform->position;
        SetTargetCoord(targetCoord);
    }
}

void Deacon::Update()
{
    Monster::Update();

    if (m_isDead)
    {
        if (m_body)
        {
            m_body->Destroy();
            m_collider->Destroy();
            m_body = nullptr;
            m_collider = nullptr;
        }
    }

    Attack(); //공격

    m_animator->SetAngle(AngleToPlayerWithSign());//플레이어기준 어디에있는지 ~몬스터 가 보는 방향과 플레이어 방향 사이의 크기 에서 보여줄 스프라이트 출력시키게 해주는거
    
    if (m_animator->IsPlayingShoot())
    {
        m_defaultEmissive = Color::white();     //데미지 이펙트 컬러
    }
    else
    {
        m_defaultEmissive = Color::black();
    }
}

void Deacon::OnDestroy()
{
    Monster::OnDestroy();
}

Collider* Deacon::InitializeCollider(GameObject* colliderObj)
{
    {
        auto renderer = colliderObj->AddComponent < UserMeshRenderer >();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh); //실린더 사용해도되지않나!? 상관노!?
        renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
        renderer->material = Resource::FindAs <Material > (BuiltInNolightTransparentMaterial);
    }
    return nullptr;
}

void Deacon::OnDamage(DamageParameters& params)
{
    if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
    {
        GameObject* bloodEffectObj = CreateGameObject();
        bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
        bloodEffectObj->AddComponent<BloodEffect>();
    }

    params.force = Vec3::zero();
    
    Explosion();
    gameObject->Destroy();
}

void Deacon::OnDead(bool& dead, DamageParameters& params)
{
}

void Deacon::SetTargetCoord(Vec3 xzCoord)
{
    m_hasTargetCoord = true;
    m_targetCoord = xzCoord;
    m_targetCoord.y = 0;
}

void Deacon::Attack()
{
    if (m_attackCount > 0)
    {
        --m_attackCount;

        m_animator->SetDefaultAnimation(m_animator->GetShoot(), true);
        Vec3 forward = Player::GetInstance()->transform->position - transform->position; //플레이어 위치 - 내 위치
        forward.y = 0;
        forward.Normalize();
        transform->forward = forward;
    }
}

void Deacon::Explosion()
{
}

void Deacon::Moving(MovingType type)
{
}
