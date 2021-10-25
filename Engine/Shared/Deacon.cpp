#include "shared_stdafx.h"
#include "Deacon.h"
#include "DeaconSpriteAnimator.h"
#include "PhysicsInitialize.h"
#include "Player.h"
#include "BloodEffect.h"
#include "PhysicsLayers.h"
#include "DeaconflyEffect.h"
#include "BillboardEffect.h"
#include "SoundMgr.h"



void Deacon::Awake()
{
    Monster::Awake();

  //  gameObject->transform->scale = Vec3::one() * 5.f;

    m_hp = 15;
    m_moveSpeed = 4.f;

    m_body->mass = 300.f;
    m_body->interpolate = Interpolate::Extrapolate;
    m_body->sleepThresholder = 2.0f;
    m_body->useGravity = false;
    //m_rendererObj->transform->scale = Vec3::one() * 10.0f;

    m_rendererObj->transform->scale = Vec3::one() * 4.0f;
    m_rendererObj->transform->localPosition = Vec3(0, -2.f, 0);

    m_renderer = CreateRenderer();

    m_animator = m_renderer->gameObject->AddComponent<DeaconSpriteAnimator>();

//    m_animator-> OnPlayedFly += Function<void()>(this, &Deacon::OnPlayedFly);
//    m_animator-> OnPlayedLand += Function<void()>(this, &Deacon::OnPlayedLand);
    m_animator-> OnPlayedAttack += Function<void()>(this, &Deacon::OnPlayedAttack);
    m_animator-> OnPlayedDie += Function<void()>(this, &Deacon::OnPlayedDie);

    m_defaultEmissive = Color::white();


   // m_rendererObj->transform->localScale 
}

void Deacon::Start()
{
    Monster::Start();

    SetBehavior(Behavior::MoveToPlayer);
}

void Deacon::FixedUpdate()
{
    Monster::FixedUpdate();

    if (Time::FixedTimeScale() == 0)
        return;
}

void Deacon::Update()
{
    Monster::Update();
    if (Time::TimeScale() == 0)
        return;

    if (isDead)
    {
        return;
    }


    float angleToPlayer = AngleToPlayerWithSign();

    m_animator->SetAngle(angleToPlayer);
    
    if (!m_isDead && m_animator->GetCurrentAnimation() != m_animator->GetShoot() || !notcreatflyeffect)
    {
        MakeFlyEffect();
    }


    if (Attacktrue)
        m_animator->PlayMove(DeaconSpriteAnimator::DIR_DECACONE::FRONT);

    BehaviorUpdate();
}

void Deacon::LateUpdate()
{
    Monster::LateUpdate();

    if (Time::TimeScale() == 0)
        return;
}

void Deacon::OnDestroy()
{
    Monster::OnDestroy();

 //   m_animator->OnPlayedFly -= Function<void()>(this, &Deacon::OnPlayedFly);
 //   m_animator->OnPlayedLand -= Function<void()>(this, &Deacon::OnPlayedLand);
    m_animator->OnPlayedAttack -= Function<void()>(this, &Deacon::OnPlayedAttack);

    if (Time::TimeScale() == 0)
        return;
}

Collider* Deacon::InitializeCollider(GameObject* colliderObj)
{
    //{
    //   // m_colliderDebugMesh = UserMesh::CreateUnmanaged<CapsuleUserMesh>();

    //    auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
    //    renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
    //}

    SphereCollider* DeaconCollider = colliderObj->AddComponent<SphereCollider>(); 

    return DeaconCollider;

    //m_collider = colliderObj->AddComponent<CapsuleCollider>();
    //return m_collider;
}

void Deacon::OnDamage(DamageParameters& params)
{
    if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
    {
        SoundMgr::Play(L"../SharedResource/Sound/zombie/zombie_hit_1.ogg", CHANNELID::DEACONHIT);

        GameObject* bloodEffectObj = CreateGameObject();
        bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
        bloodEffectObj->AddComponent<BloodEffect>();
    }
}

void Deacon::OnDead(bool& dead, DamageParameters& params)
{
    SoundMgr::Play(L"../SharedResource/Sound/zombie/zombie_helpme_1.ogg", CHANNELID::DEACONDEAD);

    notcreatflyeffect = true;
    m_animator->PlayDie();
    m_body->useGravity = true;
   // m_body->SetTranslationLockAxis(PhysicsAxis::All, false);

}

//void Deacon::OnPlayedFly()
//{
//}
//
//void Deacon::OnPlayedLand()
//{
//    SetBehavior(Behavior::ShootBall);
//}

void Deacon::OnPlayedAttack()
{

}

void Deacon::OnPlayedDie()
{
}

float Deacon::GetXZDistance(const Vec3& point) const
{
    Vec3 posxz = transform->position;
    posxz.y = 0;

    Vec3 targetxz = point;
    targetxz.y = 0;

    return Vec3::Distance(posxz, targetxz);
}

Vec3 Deacon::GetXZDirection(const Vec3& point) const
{
    Vec3 posxz = transform->position;
    posxz.y = 0;

    Vec3 targetxz = point;
    targetxz.y = 0;

    Vec3 rel = targetxz - posxz;
    Vec3 dir = rel.normalized();

    return dir;
}

bool Deacon::WallTest(const Vec3& direction) const
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
        bool isWall = angle > 30 && angle < 85;
        return isWall;
    }


    return false;
}

void Deacon::MakeFlyEffect()
{

    //createEffect += Time::DeltaTime();


    //if (createEffect > 0.1f)
    //{
    //    auto obj = CreateGameObject();
    //    float depth = (9.81f - Clamp(m_body->velocity.magnitude(), 0, 9.81f)) / 9.81f + 0.01f;

    //    obj->transform->position = m_renderer->transform->position - m_renderer->transform->forward * depth * 0.01f;
    //    obj->transform->scale = m_renderer->transform->scale;
    //    auto effect  = obj->AddComponent<DeaconflyEffect>();
    //    createEffect = 0;
    //}
}

void Deacon::SetBehavior(Behavior value)
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
    //case Behavior::FlyToPlayer:
    //    OnFlyToPlayer();
    //    break;
    //case Behavior::Landing:
    //    OnLanding();
    //    break;
    case Behavior::ShootBall:
        OnShootBall();
        break;
    case Behavior::LeftRight:
        OnLeftRight();
        break;
    }
}

void Deacon::BehaviorUpdate()
{
    switch (m_behavior)
    {
    case Behavior::Idle:
        Idle();
        break;
    case Behavior::MoveToPlayer:
        MoveToPlayer();
        break;
    //case Behavior::FlyToPlayer:
    //    FlyToPlayer();
    //    break;
    //case Behavior::Landing:
    //    Landing();
    //    break;
    case Behavior::ShootBall:
        ShootBall();
        break;
    case Behavior::LeftRight:
        LeftRight();
        break;
    }
}

void Deacon::OnIdle()
{
    m_idleAccumulate = 0.0f;

    m_animator->PlayMove(DeaconSpriteAnimator::DIR_DECACONE::FRONT);
}

void Deacon::Idle()
{
    m_idleAccumulate += Time::DeltaTime();

    if (m_idleAccumulate > 1.0f)
    {
        //int iBehavior = (rand() % (int)Behavior::RandomMax);
        //SetBehavior((Behavior)iBehavior);

        SetBehavior(Behavior::MoveToPlayer);
        m_idleAccumulate = 0;
        return;
    }
}

void Deacon::OnMoveToPlayer()
{

    if (Time::DeltaTime() == 0)
    {
        return;
    }
    m_animator->PlayMove(DeaconSpriteAnimator::DIR_DECACONE::FRONT);
    
    Vec3 target = Player::GetInstance()->transform->position;
    float d = GetXZDistance(target);
    SoundMgr::Play(L"../SharedResource/Sound/drone/Deaconfly.ogg", CHANNELID::DEACONMOVE);
    if (d < 2)
    {
        SetBehavior(Behavior::ShootBall);
        return;
    }

    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);
    transform->forward = dir * 0.5f;
    m_moveToPlayerAccumulate = 0;
}

void Deacon::MoveToPlayer()
{


    float d = GetXZDistance(Player::GetInstance()->transform->position);
    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);

    float x = transform->position.x;
    float y = transform->position.y;
    float z = transform->position.z;

    { //벽충돌확인
        PhysicsRay ray(transform->position + Vec3::down() * 0.5f * 1.5f, dir, 2.0f);
        RaycastHit hit;
        bool result =
            Physics::Raycast(
                hit,
                ray,
                (1 << (PxU32)PhysicsLayers::Terrain),
                PhysicsQueryType::Collider);

        if (result)
        {
            Attacktrue = false;
        }

    }

    {
        Vec3 dronePos = transform->position;

        Vec3 forward = Player::GetInstance()->transform->position - dronePos;
        forward.Normalize();
        transform->forward = forward;

        Vec3 xzdronePos = Vec3(dronePos.x, 0, dronePos.z);
        Vec3 playerPos = Player::GetInstance()->transform->position;
        float distance = Vec3::Distance(xzdronePos, playerPos);

        if (distance > 7.f)
        {
            m_animator->SetDefaultAnimation(m_animator->GetIdle(), true);
            //Vec3 targetCoord = Player::GetInstance()->transform->position;
            //SetTargetCoord(targetCoord);

            Vec3 velocity = forward * m_moveSpeed;
            velocity.y = 0;
            m_body->velocity = velocity;
        }

        if (distance < 1.f)
        {
            SoundMgr::Play(L"../SharedResource/Sound/drone/Deaconfly.ogg", CHANNELID::DEACONMOVE);
        }
    }

   
    if (m_body->velocity.magnitude() > m_moveSpeed * 0.5f)
    {
        m_animator->PlayDefaultAnimation ();
    }
    else
    {
        m_animator->PlayMove(DeaconSpriteAnimator::DIR_DECACONE::FRONT);
    }

    if (d < 4.0f && dir < Vec3(0,3,0))
    {
        const Vec3& playerPos = Player::GetInstance()->transform->position;
        const Vec3& gunnerPos = transform->position;
        Vec3 forward = playerPos - gunnerPos;
        forward.y = 0;
        forward.Normalize();
        transform->forward = forward;

       // m_body->SetTranslationLockAxis(PhysicsAxis::All, false);
        SetBehavior(Behavior::ShootBall);
        return;
    }


    if (d < 2.f)
    {
        SoundMgr::Play(L"../SharedResource/Sound/drone/Deaconfly.ogg", CHANNELID::DEACONMOVE);
    }

    else if (m_moveToPlayerAccumulate > 1.f)
    {
        SetBehavior(Behavior::Idle);
        m_moveToPlayerAccumulate = 0;
        return;
    }
    else
    {
        //x += dir.x * Time::DeltaTime() * 2.0f;
        //z += dir.z * Time::DeltaTime() * 2.0f;

        Vec3 vel = dir * m_moveSpeed;
        vel = ToSlopeVelocity(vel, sqrtf(1.0f));

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
            Attacktrue = true;
            y = MathEx::Lerp(y, hit.point.y + 3.0f, Time::DeltaTime() * 1.5f);
        }
    }
    
    Attacktrue = false;

    transform->position = Vec3(x, y, z);

  //  transform->position += transform->up * m_moveSpeed * Time::DeltaTime();

    m_moveToPlayerAccumulate += Time::DeltaTime();
}

//void Deacon::OnFlyToPlayer()
//{
//    Vec3 target = Player::GetInstance()->transform->position;
//
//    float d = GetXZDistance(target);
//    if (d < 3.0f + 0.1f)
//    {
//        SetBehavior(Behavior::ShootBall);
//        return;
//    }
//
//    m_animator->PlayDefaultAnimation();
//
//    m_body->SetTranslationLockAxis(PhysicsAxis::All, true);
//    m_body->useGravity = false;
//    m_body->velocity = Vec3::zero();
//}

//void Deacon::FlyToPlayer()
//{
//    float x = transform->position.x;
//    float y = transform->position.y;
//    float z = transform->position.z;
//
//
//    {   // Change y
//        PhysicsRay ray(transform->position, Vec3::down());
//        RaycastHit hit;
//        bool result =
//            Physics::Raycast(
//                hit,
//                ray,
//                (1 << (PxU32)PhysicsLayers::Terrain),
//                PhysicsQueryType::Collider);
//
//        if (result)
//        {
//            y = MathEx::Lerp(y, hit.point.y + 5.0f, Time::DeltaTime() * 3.5f);
//        }
//    }
//
//    {   // Change x, z
//        Vec3 target = Player::GetInstance()->transform->position;
//        float d = GetXZDistance(target);
//        Vec3 dir = GetXZDirection(target);
//
//        if (d < 3.0f)
//        {
//            m_body->SetTranslationLockAxis(PhysicsAxis::All, false);
//            m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
//
//           // SetBehavior(Behavior::Landing);
//            SetBehavior(Behavior::MoveToPlayer);
//            return;
//        }
//        else
//        {
//            SetBehavior(Behavior::MoveToPlayer);
//            x += dir.x * Time::DeltaTime() * 7.5f;
//            z += dir.z * Time::DeltaTime() * 7.5f;
//        }
//    }
//
//
//    transform->position = Vec3(x, y, z);
//}
//
//void Deacon::OnLanding()
//{
//}
//
//void Deacon::Landing()
//{
//}

void Deacon::OnShootBall()
{
    m_shootCount = 4;
}

void Deacon::ShootBall()
{
    Vec3 dir = GetXZDirection(Player::GetInstance()->transform->position);
    transform->forward = dir;

    //if (m_animator->IsPlayingShoot())
    //{
    //    return;
    //}

    if (m_shootWait > 0)
    {
        SoundMgr::PlayContinue(L"../SharedResource/Sound/drone/laser.ogg", CHANNELID::DEACONATTACK);
        m_shootWait -= Time::DeltaTime();
        return;
    }

    m_animator->PlayShoot();
    m_shootWait = 0.1f;

    --m_shootCount;

      ShootToPlayer();

    if (m_shootCount <= 0)
    {
        SetBehavior(Behavior::Idle);
    }
}
void Deacon::OnLeftRight()
{
}
void Deacon::LeftRight()
{
    Vec3 target = Player::GetInstance()->transform->position;
    float d = GetXZDistance(target);

    float distanceP = Vec3::Distance(target, transform->position);

    //transform->up = Vec3(0, 1, 0);
    //transform->right = Vec3::Cross(transform->up, transform->forward);
    //transform->right.Normalize();

    m_leftrightAccumulate += Time::DeltaTime();

    if (distanceP < 15.1f)
    {
        if (m_leftrightAccumulate < 2.f)
        {
            transform->position += transform->right * m_moveSpeed * Time::DeltaTime();
            m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
            m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
        }
        else
        {
            transform->position += transform->right * m_moveSpeed * -Time::DeltaTime();
            m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
            m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
            if (m_leftrightAccumulate > 3.f)
            {
                m_leftrightAccumulate = 0.f;
                //movingtype = (MovingType)3;
                SetBehavior(Deacon::Behavior::Idle);
            }
        }
    }
    else
    {
        //movingtype = (MovingType)(rand() % unsigned int(Drone::MovingType::Max));
        SetBehavior(Deacon::Behavior::Idle);
    }
}
void Deacon::ShootToPlayer()
{
    Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
    mosterToPlayer.Normalize();
    Player::GetInstance()->TakeDamage(1);
}