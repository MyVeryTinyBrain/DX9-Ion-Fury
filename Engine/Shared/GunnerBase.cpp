#include "shared_stdafx.h"
#include "GunnerBase.h"
#include "GunnerBaseAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void GunnerBase::Awake()
{
    Monster::Awake();

    m_hp = 10;
    m_moveSpeed = 3.0f;

    m_body->mass = 4.0f;
    m_body->interpolate = Interpolate::Extrapolate;
    m_body->sleepThresholder = 0.5f;

    // 렌더링되는 쿼드의 스케일을 키웁니다.
    m_rendererObj->transform->scale = Vec3::one() * 3.0f;
    m_renderer = CreateRenderer();
    m_animator = InitAnimator(m_renderer->gameObject);
    m_animator->OnDeadAnimated += Function<void()>(this, &GunnerBase::OnDeadAnimated);
}

void GunnerBase::FixedUpdate()
{
    Monster::FixedUpdate();

    if (Time::FixedTimeScale() == 0)
        return;

    if (m_isDead)
    {
        return;
    }

    // 목표 지점으로 이동하는 로직입니다.
    MoveToTarget();
}

void GunnerBase::Update()
{
    Monster::Update();

    float angleToPlayer = AngleToPlayerWithSign();

    // 몬스터의 forward 방향과 플레이어를 바라보는 방향을 계산해서 애니메이터에 전달합니다.
    m_animator->SetAngle(angleToPlayer);

    if (Time::TimeScale() == 0)
        return;

    // 몬스터의 사망이 확인되었을때
    if (m_isDead)
    {
        // 바디의 속도가 매우 작다면
        // 바디와 콜라이더 "컴포넌트" 만 삭제합니다.
        if (m_body && m_body->IsRigidbodySleep())
        {
            m_body->Destroy();
            m_collider->Destroy();
            m_body = nullptr;
            m_collider = nullptr;
        }
        return;
    }

    // 데미지 모션 중에는 동작을 하지 않습니다.

    if (!m_holdPosition)
    {
        if (/*m_behavior == BehaviorType::WalkToPlayerDirection ||*/ m_behavior == BehaviorType::WalkToRandomCoord)
        {
            Vec3 temp;
            if (Abs(angleToPlayer) < 30 &&
                (m_animator->IsPlayingIdle() || m_animator->IsPlayingWalk()) &&
                IsPlayerInSite(temp))
            {
                int attack = rand() % 100;
                if (attack > 95)
                {
                    SetBehavior(BehaviorType::Attack);
                }
            }
        }
        // 휴식시간이 아니라면 새로운 행동을 설정합니다.
        if (m_breakTime <= 0 &&
            m_animator->IsPlayingIdle() &&
            m_behavior == BehaviorType::Idle)
        {
            // 플레이어가 시야각 내에 있다면 공격합니다.
            Vec3 temp;
            if (Abs(angleToPlayer) < 30 &&
                (m_animator->IsPlayingIdle() || m_animator->IsPlayingWalk()) &&
                IsPlayerInSite(temp))
            {
                int attack = rand() % 2;
                if (attack)
                {
                    SetBehavior(BehaviorType::Attack);
                }
                else
                {
                    BehaviorType behaviorType = (BehaviorType)(rand() % unsigned int(BehaviorType::Max));
                    SetBehavior(behaviorType);
                }
            }
            else
            {
                BehaviorType behaviorType = (BehaviorType)(rand() % unsigned int(BehaviorType::Max));
                SetBehavior(behaviorType);
            }
        }
    }
    else
    {
        if (m_breakTime <= 0 &&
            m_animator->IsPlayingIdle() &&
            m_behavior == BehaviorType::Idle)
        {
            SetBehavior(BehaviorType::Attack);
        }
    }

    // 정지 상태일때만 휴식시간을 감소시킵니다.
    if (m_breakTime > 0 &&
        m_behavior == BehaviorType::Idle &&
        m_animator->IsPlayingIdle())
    {
        m_breakTime -= Time::DeltaTime();
    }

    // 현재 속도가 지정속도 이상이면 걷는 애니메이션을 출력합니다.
    // 아니라면 정지 애니메이션을 출력합니다.
    if (m_animator->IsPlayingIdle() &&
        m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
    {
        m_animator->PlayWalk();
    }
    else if (m_animator->IsPlayingWalk() &&
        m_body->velocity.magnitude() < m_moveSpeed * 0.5f)
    {
        m_animator->PlayDefaultAnimation();
    }

    // 공격해야하는 경우에 공격합니다.
    Attack();

    // 발사 애니메이션 중에 발광합니다.
    if (m_animator->IsPlayingShoot())
    {
        m_defaultEmissive = Color::white();
    }
    else
    {
        m_defaultEmissive = Color::black();
    }
}

void GunnerBase::OnDestroy()
{
    Monster::OnDestroy();

    m_animator->OnDeadAnimated -= Function<void()>(this, &GunnerBase::OnDeadAnimated);

    if (Time::TimeScale() == 0)
        return;
}

Collider* GunnerBase::InitializeCollider(GameObject* colliderObj)
{
    //{
    //    auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
    //    renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
    //}

    m_capsuleCollider = colliderObj->AddComponent<CapsuleCollider>();
    return m_capsuleCollider;
}

void GunnerBase::OnDamage(DamageParameters& params)
{
    m_hasTargetCoord = false;
    SetBehavior(BehaviorType::Attack);
    m_attackWaitCounter = GetDamagedRevengeAttackWaitTime();

    switch (params.damageType)
    {
        case MonsterDamageType::Bullet:
        case MonsterDamageType::Explosion:
            m_animator->PlayDamage(GunnerBaseAnimator::DAMAGE::DAMAGE_GENERIC);
            break;
        case MonsterDamageType::Zizizik:
            m_animator->PlayDamage(GunnerBaseAnimator::DAMAGE::DAMAGE_ZIZIZIK);
            break;
    }

    if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
    {
        GameObject* bloodEffectObj = CreateGameObject();
        bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
        bloodEffectObj->AddComponent<BloodEffect>();
    }

    // 피격당하면 플레이어를 바라봅니다.
    const Vec3& playerPos = Player::GetInstance()->transform->position;
    const Vec3& gunnerPos = transform->position;
    Vec3 forward = playerPos - gunnerPos;
    forward.y = 0;
    forward.Normalize();
    transform->forward = forward;
}

void GunnerBase::OnDead(bool& dead, DamageParameters& params)
{
    m_hasTargetCoord = false;
    m_attackCount = 0;
    m_breakTime = FLT_MAX;

    // 우선 애니메이션 종류를 랜덤으로 선택합니다.
    int dieIndex = rand() % (int)GunnerBaseAnimator::DIE::MAX;

    // 만약 폭발에 의한 죽음이라면 폭발 애니메이션을 선택합니다.
    if (params.damageType == MonsterDamageType::Explosion)
    {
        dieIndex = (int)MonsterDamageType::Explosion;
    }

    m_animator->PlayDie((GunnerBaseAnimator::DIE)dieIndex);
}

void GunnerBase::OnDeadAnimated()
{
    //gameObject->Destroy();
}

bool GunnerBase::IsPlayerInSite(Vec3& playerCoord)
{
    Vec3 playerHead = Player::GetInstance()->perspectiveCamera->transform->position;
    Vec3 monsterHead = transform->position + Vec3::up() * 0.5f;

    Vec3 mosterToPlayer = playerHead - monsterHead;
    mosterToPlayer.Normalize();

    PhysicsRay ray(monsterHead, mosterToPlayer, FLT_MAX);
    RaycastHit hit;
    Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::Collider);

    if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Player)
    {
        playerCoord = playerHead;
        return true;
    }

    return false;
}

void GunnerBase::MoveToTarget()
{   
    // 목표 지점이 없다면 종료합니다.
    if (!m_hasTargetCoord)
    {
        return;
    }

    const Vec3& gunnerPos = transform->position;

    // xz 평면에서의 목표까지의 방향 벡터를 설정합니다.
    Vec3 forward = m_targetCoord - gunnerPos;
    forward.y = 0;
    forward.Normalize();

    // 바라보는 방향을 설정합니다.
    transform->forward = forward;

    // 몬스터의 위치를 xz 평면위의 좌표로 계산합니다.
    Vec3 xzGunnerPos = Vec3(gunnerPos.x, 0, gunnerPos.z);

    // xz 평면위에서의 목표지점까지의 거리를 계산합니다.
    float distance = Vec3::Distance(xzGunnerPos, m_targetCoord);

    if (distance > 2.1f)
    {
        // 지정한 거리보다 먼 경우에 실행됩니다.

        // 몬스터가 바라보는 방향으로 레이를 발사합니다.
        PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
        RaycastHit hit;

        // (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster): Terrain, Monster 레이어만 쿼리합니다.
        if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
        {
            // 충돌한 콜라이더 면의 노멀 벡터와 업 벡터와의 각도를 구합니다.
            float angle = Vec3::Angle(hit.normal, Vec3::up());

            if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain && angle > 85 && angle < 95)
            {
                // 충돌한 콜라이더가 Terrain인 경우에
                // 각도가 지정 각도 이내이면 벽이라고 판단하여 목표 지점을 없앱니다.
                m_hasTargetCoord = false;
                SetBehavior(BehaviorType::Idle);
                return;
            }
            else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
            {
                // 충돌한 콜라이더가 몬스터 콜라이더면
                // 목표 지점을 없앱니다.
                m_hasTargetCoord = false;
                SetBehavior(BehaviorType::Idle);
                return;
            }
        }

        // 속도를 설정합니다.
        Vec3 acceleration = forward * m_moveSpeed;
        Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
        velocity.y = m_body->velocity.y;
        m_body->velocity = velocity;

        if (Vec3::Distance(xzGunnerPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
        {
            // 이전 몬스터 좌표와 현재 몬스터 좌표의 거리를 비교해서
            // 지정한 거리 이내이면
            // 몬스터가 걸려서 움직이지 못한다고 판단하여 목표 지점을 없앱니다.

            m_hasTargetCoord = false;
            SetBehavior(BehaviorType::Idle);
            return;
        }

        // 현재 위치를 저장합니다.
        m_beforeCoord = transform->position;
        m_beforeCoord.y = 0;
    }
    else
    {
        // 저정한 거리보다 가까운 경우에는 목표 지점을 없앱니다.
        m_hasTargetCoord = false;
        SetBehavior(BehaviorType::Idle);
    }
}

void GunnerBase::SetTargetCoord(Vec3 xzCoord)
{
    m_hasTargetCoord = true;
    m_targetCoord = xzCoord;
    m_targetCoord.y = 0;

    Vec3 forward = xzCoord - transform->position;
    forward.y = 0;
    forward.Normalize();
    transform->forward = forward;
}

void GunnerBase::Attack()
{    
    // 발사 애니메이션 중일때 종료합니다.
    if (m_animator->IsPlayingShoot())
    {
        return;
    }

    if (m_attackWaitCounter > 0)
    {
        m_attackWaitCounter -= Time::DeltaTime();
        return;
    }

    // 공격 카운터가 남아있다면 공격합니다.
    if (m_attackCount > 0)
    {
        --m_attackCount;
        m_animator->PlayShoot();

        // 플레이어를 바라봅니다.
        Vec3 forward = Player::GetInstance()->transform->position - transform->position;
        forward.y = 0;
        forward.Normalize();
        transform->forward = forward;

        // 플레이어에게 총을 쏩니다.
        ShootToPlayer();

        if (m_attackCount <= 0)
        {
            SetBehavior(BehaviorType::Idle);
        }
    }

    if (m_behavior == BehaviorType::Attack && m_attackCount <= 0)
    {
        SetBehavior(BehaviorType::Idle);
        return;
    }
}

void GunnerBase::SetBehavior(BehaviorType type)
{
    m_hasTargetCoord = false;
    m_attackCount = 0;
    m_breakTime = GetBreakTime();

    switch (type)
    {
        case BehaviorType::Idle:
            {
            }
            break;
        case BehaviorType::WalkToRandomCoord:
            {
                float randomRadian = (rand() % 360) * Deg2Rad;
                float randomDistance = (rand() % 15) + 2.1f + 0.1f;
                Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
                SetTargetCoord(targetCoord);
            }
            break;
        case BehaviorType::WalkToPlayerDirection:
            {
                const Vec3& monsterPos = transform->position;
                const Vec3& playerPos = Player::GetInstance()->transform->position;
                Vec3 relative = playerPos - monsterPos;
                float distance = Clamp(relative.magnitude(), 0, 8.0f);
                Vec3 direction = relative.normalized();
                SetTargetCoord(monsterPos + direction * distance);
            }
            break;
        case BehaviorType::Attack:
            {
                Vec3 playerCoord;
                if (IsPlayerInSite(playerCoord))
                {
                    m_attackCount = GetAttackCount();
                    m_attackWaitCounter = 0.05f + float(rand() % 15) * 0.01f + GetAttackWaitTime();
                }
                else
                {
                    SetBehavior(BehaviorType::Idle);
                }
            }
            break;
    }

    m_behavior = type;
}
