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

    // �������Ǵ� ������ �������� Ű��ϴ�.
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

    // ��ǥ �������� �̵��ϴ� �����Դϴ�.
    MoveToTarget();
}

void GunnerBase::Update()
{
    Monster::Update();

    float angleToPlayer = AngleToPlayerWithSign();

    // ������ forward ����� �÷��̾ �ٶ󺸴� ������ ����ؼ� �ִϸ����Ϳ� �����մϴ�.
    m_animator->SetAngle(angleToPlayer);

    if (Time::TimeScale() == 0)
        return;

    // ������ ����� Ȯ�εǾ�����
    if (m_isDead)
    {
        // �ٵ��� �ӵ��� �ſ� �۴ٸ�
        // �ٵ�� �ݶ��̴� "������Ʈ" �� �����մϴ�.
        if (m_body && m_body->IsRigidbodySleep())
        {
            m_body->Destroy();
            m_collider->Destroy();
            m_body = nullptr;
            m_collider = nullptr;
        }
        return;
    }

    // ������ ��� �߿��� ������ ���� �ʽ��ϴ�.

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
        // �޽Ľð��� �ƴ϶�� ���ο� �ൿ�� �����մϴ�.
        if (m_breakTime <= 0 &&
            m_animator->IsPlayingIdle() &&
            m_behavior == BehaviorType::Idle)
        {
            // �÷��̾ �þ߰� ���� �ִٸ� �����մϴ�.
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

    // ���� �����϶��� �޽Ľð��� ���ҽ�ŵ�ϴ�.
    if (m_breakTime > 0 &&
        m_behavior == BehaviorType::Idle &&
        m_animator->IsPlayingIdle())
    {
        m_breakTime -= Time::DeltaTime();
    }

    // ���� �ӵ��� �����ӵ� �̻��̸� �ȴ� �ִϸ��̼��� ����մϴ�.
    // �ƴ϶�� ���� �ִϸ��̼��� ����մϴ�.
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

    // �����ؾ��ϴ� ��쿡 �����մϴ�.
    Attack();

    // �߻� �ִϸ��̼� �߿� �߱��մϴ�.
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

    // �ǰݴ��ϸ� �÷��̾ �ٶ󺾴ϴ�.
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

    // �켱 �ִϸ��̼� ������ �������� �����մϴ�.
    int dieIndex = rand() % (int)GunnerBaseAnimator::DIE::MAX;

    // ���� ���߿� ���� �����̶�� ���� �ִϸ��̼��� �����մϴ�.
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
    // ��ǥ ������ ���ٸ� �����մϴ�.
    if (!m_hasTargetCoord)
    {
        return;
    }

    const Vec3& gunnerPos = transform->position;

    // xz ��鿡���� ��ǥ������ ���� ���͸� �����մϴ�.
    Vec3 forward = m_targetCoord - gunnerPos;
    forward.y = 0;
    forward.Normalize();

    // �ٶ󺸴� ������ �����մϴ�.
    transform->forward = forward;

    // ������ ��ġ�� xz ������� ��ǥ�� ����մϴ�.
    Vec3 xzGunnerPos = Vec3(gunnerPos.x, 0, gunnerPos.z);

    // xz ����������� ��ǥ���������� �Ÿ��� ����մϴ�.
    float distance = Vec3::Distance(xzGunnerPos, m_targetCoord);

    if (distance > 2.1f)
    {
        // ������ �Ÿ����� �� ��쿡 ����˴ϴ�.

        // ���Ͱ� �ٶ󺸴� �������� ���̸� �߻��մϴ�.
        PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
        RaycastHit hit;

        // (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster): Terrain, Monster ���̾ �����մϴ�.
        if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
        {
            // �浹�� �ݶ��̴� ���� ��� ���Ϳ� �� ���Ϳ��� ������ ���մϴ�.
            float angle = Vec3::Angle(hit.normal, Vec3::up());

            if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain && angle > 85 && angle < 95)
            {
                // �浹�� �ݶ��̴��� Terrain�� ��쿡
                // ������ ���� ���� �̳��̸� ���̶�� �Ǵ��Ͽ� ��ǥ ������ ���۴ϴ�.
                m_hasTargetCoord = false;
                SetBehavior(BehaviorType::Idle);
                return;
            }
            else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
            {
                // �浹�� �ݶ��̴��� ���� �ݶ��̴���
                // ��ǥ ������ ���۴ϴ�.
                m_hasTargetCoord = false;
                SetBehavior(BehaviorType::Idle);
                return;
            }
        }

        // �ӵ��� �����մϴ�.
        Vec3 acceleration = forward * m_moveSpeed;
        Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
        velocity.y = m_body->velocity.y;
        m_body->velocity = velocity;

        if (Vec3::Distance(xzGunnerPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
        {
            // ���� ���� ��ǥ�� ���� ���� ��ǥ�� �Ÿ��� ���ؼ�
            // ������ �Ÿ� �̳��̸�
            // ���Ͱ� �ɷ��� �������� ���Ѵٰ� �Ǵ��Ͽ� ��ǥ ������ ���۴ϴ�.

            m_hasTargetCoord = false;
            SetBehavior(BehaviorType::Idle);
            return;
        }

        // ���� ��ġ�� �����մϴ�.
        m_beforeCoord = transform->position;
        m_beforeCoord.y = 0;
    }
    else
    {
        // ������ �Ÿ����� ����� ��쿡�� ��ǥ ������ ���۴ϴ�.
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
    // �߻� �ִϸ��̼� ���϶� �����մϴ�.
    if (m_animator->IsPlayingShoot())
    {
        return;
    }

    if (m_attackWaitCounter > 0)
    {
        m_attackWaitCounter -= Time::DeltaTime();
        return;
    }

    // ���� ī���Ͱ� �����ִٸ� �����մϴ�.
    if (m_attackCount > 0)
    {
        --m_attackCount;
        m_animator->PlayShoot();

        // �÷��̾ �ٶ󺾴ϴ�.
        Vec3 forward = Player::GetInstance()->transform->position - transform->position;
        forward.y = 0;
        forward.Normalize();
        transform->forward = forward;

        // �÷��̾�� ���� ���ϴ�.
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
