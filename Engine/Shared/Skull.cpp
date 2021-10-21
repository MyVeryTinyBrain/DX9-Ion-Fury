#include "shared_stdafx.h"
#include "Skull.h"
#include "SkullAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "BloodEffect.h"
#include "SkullBall.h"
#include "SkullReplica.h"
#include "BillboardEffect.h"

void Skull::Awake()
{
    Monster::Awake();

    gameObject->transform->scale = Vec3::one() * 1.5f;

    m_hp = 300.0f;
    m_moveSpeed = 3.0f;

    m_body->mass = 10.0f;
    m_body->interpolate = Interpolate::Extrapolate;
    m_body->sleepThresholder = 2.0f;

    m_rendererObj->transform->localScale = Vec3::one() * 3.0f;
    m_renderer = CreateRenderer();
    m_animator = m_renderer->gameObject->AddComponent<SkullAnimator>();
    m_animator->OnPlayedFly += Function<void()>(this, &Skull::OnPlayedFly);
    m_animator->OnPlayedLand += Function<void()>(this, &Skull::OnPlayedLand);
    m_animator->OnPlayedAttack += Function<void()>(this, &Skull::OnPlayedAttack);
    m_animator->OnPlayedDie += Function<void()>(this, &Skull::OnPlayedDie);

    m_replicaRoot = CreateGameObjectToChild(transform);

    m_defaultEmissive = Color::white();

    SetBehavior(Behavior::Idle);
}

void Skull::FixedUpdate()
{
    Monster::FixedUpdate();
}

void Skull::Update()
{
    Monster::Update();

    if (isDead)
    {
        return;
    }

    float angleToPlayer = AngleToPlayerWithSign();

    m_animator->SetAngle(angleToPlayer);

    BehaviorUpdate();
}

void Skull::LateUpdate()
{
    Monster::LateUpdate();

    if (m_flyEffectCounter > 0)
    {
        m_flyEffectCounter -= Time::DeltaTime();
    }
    if (m_animator->IsPlayingFly() && m_collider->enable && m_flyEffectCounter <= 0)
    {
        MakeFlyEffect();

        m_flyEffectCounter = 0.015f;
    }
}

void Skull::OnDestroy()
{
    Monster::OnDestroy();

    m_animator->OnPlayedFly -= Function<void()>(this, &Skull::OnPlayedFly);
    m_animator->OnPlayedLand -= Function<void()>(this, &Skull::OnPlayedLand);
    m_animator->OnPlayedAttack -= Function<void()>(this, &Skull::OnPlayedAttack);

    if (m_colliderDebugMesh)
    {
        m_colliderDebugMesh->ReleaseUnmanaged();
        m_colliderDebugMesh = nullptr;
    }
}

Collider* Skull::InitializeCollider(GameObject* colliderObj)
{
    //{
    //    m_colliderDebugMesh = UserMesh::CreateUnmanaged<CapsuleUserMesh>();

    //    m_colliderDebugRenderer = colliderObj->AddComponent<UserMeshRenderer>();
    //    m_colliderDebugRenderer->userMesh = m_colliderDebugMesh;
    //    m_colliderDebugRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
    //    m_colliderDebugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
    //}

    m_collider = colliderObj->AddComponent<CapsuleCollider>();
    return m_collider;
}

void Skull::OnDamage(DamageParameters& params)
{
    if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
    {
        GameObject* bloodEffectObj = CreateGameObject();
        bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
        bloodEffectObj->AddComponent<BloodEffect>();
    }
}

void Skull::OnDead(bool& dead, DamageParameters& params)
{
    m_body->SetTranslationLockAxis(PhysicsAxis::All, false);
    m_body->useGravity = true;

    m_animator->PlayDie();
}

void Skull::OnPlayedFly()
{
}

void Skull::OnPlayedLand()
{
    SetBehavior(Behavior::ShootBall);
}

void Skull::OnPlayedAttack()
{
    Vec3 monsterHead = transform->position + Vec3::up() * 0.75f * 1.5f;
    Vec3 playerHead = Player::GetInstance()->perspectiveCamera->transform->position;

    Vec3 monsterToPlayer = playerHead - monsterHead;
    Vec3 dir = monsterToPlayer.normalized();

    GameObject* obj = CreateGameObject();
    obj->transform->position = monsterHead;

    SkullBall* ball = obj->AddComponent<SkullBall>();
    ball->SetVelocity(dir * 20);
}

void Skull::OnPlayedDie()
{
}

float Skull::GetXZDistance(const Vec3& point) const
{
    Vec3 posxz = transform->position;
    posxz.y = 0;

    Vec3 targetxz = point;
    targetxz.y = 0;

    return Vec3::Distance(posxz, targetxz);
}

Vec3 Skull::GetXZDirection(const Vec3& point) const
{
    Vec3 posxz = transform->position;
    posxz.y = 0;

    Vec3 targetxz = point;
    targetxz.y = 0;

    Vec3 rel = targetxz - posxz;
    Vec3 dir = rel.normalized();

    return dir;
}

bool Skull::WallTest(const Vec3& direction) const
{
    PhysicsRay ray(transform->position + Vec3::down() * 0.5f * 1.5f, direction, 2.0f);
    RaycastHit hit;
    bool result =
        Physics::Raycast(
            hit,
            ray,
            (1 << (PxU32)PhysicsLayers::Terrain),
            PhysicsQueryType::Collider);

    if (!result)
    {
        return false;
    }
    else
    {
        float angle = Vec3::Angle(hit.normal, Vec3::up());
        bool isWall = angle > 85 && angle < 95;
        return isWall;
    }

    return false;
}

void Skull::MakeFlyEffect()
{
    float depth = (9.81f - Clamp(m_body->velocity.magnitude(), 0, 9.81f)) / 9.81f + 0.01f;

    GameObject* obj = CreateGameObject();
    obj->transform->position = m_renderer->transform->position - m_renderer->transform->forward * depth * 0.01f;
    obj->transform->scale = m_renderer->transform->scale;

    BillboardEffect* effect = obj->AddComponent<BillboardEffect>();
    effect->AddTexture(L"../SharedResource/Texture/skull/fly3.png");
    effect->SetInterval(0.2f);

    effect->GetBillboardRenderer()->freezeX = true;
    effect->GetBillboardRenderer()->freezeZ = true;
}

void Skull::SetBehavior(Behavior value)
{
    if (value == Behavior::None || value == Behavior::RandomMax)
    {
        return;
    }

    if (value == m_behavior)
    {
        return;
    }

    m_behavior = value;

    switch (m_behavior)
    {
        case Behavior::Idle:
            OnIdle();
            break;
        case Behavior::MoveToPlayer:
            OnMoveToPlayer();
            break;
        case Behavior::FlyToPlayer:
            OnFlyToPlayer();
            break;
        case Behavior::Landing:
            OnLanding();
            break;
        case Behavior::ShootBall:
            OnShootBall();
            break;
        case Behavior::FlyReplica:
            OnFlyReplica();
            break;
        case Behavior::EndReplica:
            OnEndReplica();
            break;
    }
}

void Skull::BehaviorUpdate()
{
    switch (m_behavior)
    {
        case Behavior::Idle:
            Idle();
            break;
        case Behavior::MoveToPlayer:
            MoveToPlayer();
            break;
        case Behavior::FlyToPlayer:
            FlyToPlayer();
            break;
        case Behavior::Landing:
            Landing();
            break;
        case Behavior::ShootBall:
            ShootBall();
            break;        
		case Behavior::FlyReplica:
			FlyReplica();
			break;
		case Behavior::EndReplica:
			EndReplica();
			break;
    }
}

void Skull::OnIdle()
{
    m_idleAccumulate = 0.0f;

    m_animator->PlayIdle();
}

void Skull::Idle()
{
    m_idleAccumulate += Time::DeltaTime();

    if (m_idleAccumulate > 1.0f)
    {
        int iBehavior = (rand() % (int)Behavior::RandomMax);
        SetBehavior((Behavior)iBehavior);
        return;
    }
}

void Skull::OnMoveToPlayer()
{
    Vec3 target = Player::GetInstance()->transform->position;
    float d = GetXZDistance(target);
    if (d < 3.0f + 0.1f)
    {
        SetBehavior(Behavior::ShootBall);
        return;
    }

    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);
    transform->forward = dir;
    m_moveToPlayerAccumulate = 0;
}

void Skull::MoveToPlayer()
{
    float d = GetXZDistance(Player::GetInstance()->transform->position);
    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);

    if (m_body->velocity.magnitude() > m_moveSpeed * 0.5f)
    {
        m_animator->PlayWalk();
    }
    else
    {
        m_animator->PlayIdle();
    }

    if (d < 3.0f)
    {
        SetBehavior(Behavior::Idle);
    }
    else if (WallTest(dir))
    {
        SetBehavior(Behavior::FlyToPlayer);
        return;
    }
    else if (m_moveToPlayerAccumulate > 3.0f)
    {
        SetBehavior(Behavior::ShootBall);
    }
    else
    {
        Vec3 vel = dir * m_moveSpeed;
        vel = ToSlopeVelocity(vel, sqrtf(2.0f) * 1.5f);
        
        if (Abs(vel.y) < 0.1f)
        {
            m_body->velocity = Vec3(vel.x, m_body->velocity.y, vel.z);
        }
        else
        {
            m_body->velocity = vel;
        }

        transform->forward = dir;
    }

    m_moveToPlayerAccumulate += Time::DeltaTime();
}

void Skull::OnFlyToPlayer()
{
    Vec3 target = Player::GetInstance()->transform->position;

    float d = GetXZDistance(target);
    if (d < 3.0f + 0.1f)
    {
        SetBehavior(Behavior::ShootBall);
        return;
    }

    m_animator->PlayFly();

    m_body->SetTranslationLockAxis(PhysicsAxis::All, true);
    m_body->useGravity = false;
    m_body->velocity = Vec3::zero();
}

void Skull::FlyToPlayer()
{
    float x = transform->position.x;
    float y = transform->position.y;
    float z = transform->position.z;

    {   // Change y
        PhysicsRay ray(transform->position, Vec3::down());
        RaycastHit hit;
        bool result =
            Physics::Raycast(
                hit,
                ray,
                (1 << (PxU32)PhysicsLayers::Terrain),
                PhysicsQueryType::Collider);

        if (result)
        {
            y = MathEx::Lerp(y, hit.point.y + 5.0f, Time::DeltaTime() * 3.5f);
        }
    }

    {   // Change x, z
        Vec3 target = Player::GetInstance()->transform->position;
        float d = GetXZDistance(target);
        Vec3 dir = GetXZDirection(target);

        if (d < 3.0f)
        {
            m_body->SetTranslationLockAxis(PhysicsAxis::All, false);
            m_body->useGravity = true;

            SetBehavior(Behavior::Landing);
            return;
        }
        else
        {
            x += dir.x * Time::DeltaTime() * 7.5f;
            z += dir.z * Time::DeltaTime() * 7.5f;
        }
    }

    transform->position = Vec3(x, y, z);
}

void Skull::OnLanding()
{
    m_body->SetTranslationLockAxis(PhysicsAxis::All, false);
    m_body->useGravity = true;
}

void Skull::Landing()
{
    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);
    transform->forward = dir;

    SweepHit hit;
    bool result =
        Physics::SweepCollider(hit,
            m_collider,
            Vec3::down(),
            1.0f,
            (1 << (PxU32)PhysicsLayers::Terrain),
            PhysicsQueryType::Collider);

    if (result)
    {
        m_animator->PlayLand();
    }
}

void Skull::OnShootBall()
{
    m_shootCount = 10;
}

void Skull::ShootBall()
{
    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);
    transform->forward = dir;

    if (m_animator->IsPlayingAttack())
    {
        return;
    }

    if (m_shootWait > 0)
    {
        m_shootWait -= Time::DeltaTime();
        return;
    }

    m_animator->PlayAttack();

    m_shootWait = 0.1f;

    --m_shootCount;

    if (m_shootCount <= 0)
    {
        SetBehavior(Behavior::Idle);
    }
}

void Skull::OnFlyReplica()
{
    m_animator->PlayFly();

    m_body->SetTranslationLockAxis(PhysicsAxis::All, true);
    m_body->useGravity = false;
    m_body->velocity = Vec3::zero();

    m_hasReplicas = false;
    m_replicaLocalDistance = 0.0f;
}

void Skull::FlyReplica()
{
    float x = transform->position.x;
    float y = transform->position.y;
    float z = transform->position.z;

    {   // Change y
        PhysicsRay ray(transform->position, Vec3::down());
        RaycastHit hit;
        bool result =
            Physics::Raycast(
                hit,
                ray,
                (1 << (PxU32)PhysicsLayers::Terrain),
                PhysicsQueryType::Collider);

        float targetY = hit.point.y + 7.0f;

        if (result)
        {
            y = MathEx::Lerp(y, targetY, Time::DeltaTime() * 3.5f);
        }

        if (Abs(y - targetY) < 0.25f)
        {
            if (!m_hasReplicas)
            {
                for (int i = 0; i < REPLICA_MAX; ++i)
                {
                    float percent = float(i) / float(REPLICA_MAX);
                    float radian = percent * TAU;

                    auto replicaObj = CreateGameObjectToChild(m_replicaRoot->transform);
                    replicaObj->transform->localPosition = Vec3(cosf(radian), 0.0f, sinf(radian));

                    m_replicas[i] = replicaObj->AddComponent<SkullReplica>();
                }

                m_collider->enable = false;
                m_renderer->enable = false;

                m_hasReplicas = true;
            }
        }
    }

    {   // Change x, z
        Vec3 target = Player::GetInstance()->transform->position;
        float d = GetXZDistance(target);
        Vec3 dir = GetXZDirection(target);

        if (d > 6.0f)
        {
            x += dir.x * Time::DeltaTime() * 2.0f;
            z += dir.z * Time::DeltaTime() * 2.0f;
        }
    }

    transform->position = Vec3(x, y, z);

    if (!m_hasReplicas)
    {
        return;
    }

    float target = 3.0f;

    m_replicaLocalDistance = MathEx::Lerp(m_replicaLocalDistance, target, Time::DeltaTime() * 2.5f);

    int deadCount = 0;
    for (int i = 0; i < REPLICA_MAX; ++i)
    {
        m_replicas[i]->SetLocalDistance(m_replicaLocalDistance);

        if (m_replicas[i]->isDead)
        {
            ++deadCount;
        }
    }

    {
        Vec3 localEulerAngle = m_replicaRoot->transform->localEulerAngle;
        localEulerAngle.y += 90.0f * Time::DeltaTime();
        m_replicaRoot->transform->localEulerAngle = localEulerAngle;
    }

    if (deadCount == REPLICA_MAX)
    {
        SetBehavior(Behavior::EndReplica);
    }
}

void Skull::OnEndReplica()
{

}

void Skull::EndReplica()
{
    float x = transform->position.x;
    float y = transform->position.y;
    float z = transform->position.z;

    {   // Change y
        PhysicsRay ray(transform->position, Vec3::down());
        RaycastHit hit;
        bool result =
            Physics::Raycast(
                hit,
                ray,
                (1 << (PxU32)PhysicsLayers::Terrain),
                PhysicsQueryType::Collider);

        float targetY = 7.0f;

        if (result)
        {
            y = MathEx::Lerp(y, hit.point.y + targetY, Time::DeltaTime() * 3.5f);
        }
    }

    transform->position = Vec3(x, y, z);

    m_replicaLocalDistance = MathEx::Lerp(m_replicaLocalDistance, 0.0f, Time::DeltaTime() * 2.5f);

    for (int i = 0; i < REPLICA_MAX; ++i)
    {
        if (!m_replicas[i].IsNull())
        {
            m_replicas[i]->SetLocalDistance(m_replicaLocalDistance);
        }
    }

    if (m_replicaLocalDistance <= 0.05f)
    {
        for (int i = 0; i < REPLICA_MAX; ++i)
        {
            if (!m_replicas[i].IsNull())
            {
                m_replicas[i]->gameObject->Destroy();
            }
        }

        m_collider->enable = true;
        m_renderer->enable = true;

        SetBehavior(Behavior::Landing);
        return;
    }
}
