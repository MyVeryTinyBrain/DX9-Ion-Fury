#include "stdafx.h"
#include "Gunner.h"
#include "GunnerSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void Gunner::Awake()
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

    m_animator = m_renderer->gameObject->AddComponent<GunnerSpriteAnimator>();
    m_animator->OnDeadAnimated += Function<void()>(this, &Gunner::OnDeadAnimated);
}

void Gunner::FixedUpdate()
{
    Monster::FixedUpdate();

    if (m_isDead)
    {
        return;
    }

    // ��ǥ �������� �̵��ϴ� �����Դϴ�.
    MoveToTarget();
}

void Gunner::Update()
{
    Monster::Update();

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
    if (m_animator->IsPlayingDamage())
    {
        return;
    }

    // �޽Ľð��� �ƴ϶�� ���ο� �ൿ�� �����մϴ�.
    if (m_breakTime <= 0)
    {
        BehaviorType behaviorType = (BehaviorType)(rand() % unsigned int(BehaviorType::Max));
        SetBehavior(behaviorType);
    }

    // ���� �����϶��� �޽Ľð��� ���ҽ�ŵ�ϴ�.
    if (m_breakTime > 0 &&
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

    // ������ forward ����� �÷��̾ �ٶ󺸴� ������ ����ؼ� �ִϸ����Ϳ� �����մϴ�.
    m_animator->SetAngle(AngleToPlayerWithSign());

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

void Gunner::OnDestroy()
{
    Monster::OnDestroy();

    m_animator->OnDeadAnimated -= Function<void()>(this, &Gunner::OnDeadAnimated);
}

Collider* Gunner::InitializeCollider(GameObject* colliderObj)
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

void Gunner::OnDamage(DamageParameters& params)
{
    m_hasTargetCoord = false;
    m_attackCount = 5;
    m_breakTime = 0.35f;

    switch (params.damageType)
    {
        case MonsterDamageType::Bullet:
        case MonsterDamageType::Explosion:
            m_animator->PlayDamage(GunnerSpriteAnimator::DAMAGE::DAMAGE_GENERIC);
            break;
        case MonsterDamageType::Zizizik:
            m_animator->PlayDamage(GunnerSpriteAnimator::DAMAGE::DAMAGE_ZIZIZIK);
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

void Gunner::OnDead(bool& dead, DamageParameters& params)
{
    m_hasTargetCoord = false;
    m_attackCount = 0;
    m_breakTime = FLT_MAX;

    // �켱 �ִϸ��̼� ������ �������� �����մϴ�.
    int dieIndex = rand() % (int)GunnerSpriteAnimator::DIE::MAX;

    // ���� ���߿� ���� �����̶�� ���� �ִϸ��̼��� �����մϴ�.
    if (params.damageType == MonsterDamageType::Explosion)
    {
        dieIndex = (int)MonsterDamageType::Explosion;
    }

    m_animator->PlayDie((GunnerSpriteAnimator::DIE)dieIndex);
}

void Gunner::OnDeadAnimated()
{
    //gameObject->Destroy();
}

bool Gunner::PlayerInSite() const
{
    return false;
}

void Gunner::MoveToTarget()
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
                return;
            }
            else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
            {
                // �浹�� �ݶ��̴��� ���� �ݶ��̴���
                // ��ǥ ������ ���۴ϴ�.
                m_hasTargetCoord = false;
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
    }
}

void Gunner::SetTargetCoord(Vec3 xzCoord)
{
    m_hasTargetCoord = true;
    m_targetCoord = xzCoord;
    m_targetCoord.y = 0;
}

void Gunner::Attack()
{
    // �߻� �ִϸ��̼� ���϶� �����մϴ�.
    if (m_animator->IsPlayingShoot())
    {
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
    }
}

void Gunner::SetBehavior(BehaviorType type)
{
    m_hasTargetCoord = false;
    m_attackCount = 0;
    m_breakTime = 0.35f;

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
                m_attackCount = 5;
            }
            break;
    }
}

void Gunner::ShootToPlayer()
{
    Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
    mosterToPlayer.Normalize();
    Player::GetInstance()->TakeDamage(5, mosterToPlayer * 2.0f);
}
