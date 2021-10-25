#include "shared_stdafx.h"
#include "ObjectRat.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "ObjectRatAnimator.h"

void ObjectRat::Awake()
{
    m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();

    auto rendererObj = CreateGameObjectToChild(transform);
    rendererObj->transform->localPosition = Vec3(0, 0.5f, 0);
    rendererObj->transform->localScale = Vec3(2, 2, 2);

    auto renderer = rendererObj->AddComponent<UserMeshBillboardRenderer>();
    renderer->freezeX = true;
    renderer->freezeZ = true;
    renderer->material = Resource::FindAs<Material>(BuiltInAlphaTestMaterial);
    renderer->userMesh = m_quad;

    m_animator = rendererObj->AddComponent<ObjectRatAnimator>();

	//{
 //       auto debugRendererObj = CreateGameObjectToChild(transform);
 //       m_debugRenderer = debugRendererObj->AddComponent<UserMeshRenderer>();
 //       m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
 //       m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
 //       m_debugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}
}

void ObjectRat::Start()
{
    if (Time::TimeScale() == 0)
    {
        return;
    }

    PhysicsRay ray(transform->position + Vec3::up() * m_radius, Vec3::down(), 50.0f);
    RaycastHit hit;
    if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider))
    {
        transform->position = hit.point + Vec3::up() * m_radius;
    }

    m_initCoord = transform->position;
}

void ObjectRat::Update()
{
    float angleToPlayer = AngleToPlayerWithSign();

    m_animator->SetAngle(angleToPlayer);

    if (m_debugRenderer)
    {
        m_debugRenderer->gameObject->transform->localScale = Vec3::one() * m_radius * 2.0f;
    }

    if (Time::TimeScale() == 0)
    {
        return;
    }

    if (!m_hasTargetCoord)
    {
        if (m_breakTime > 0)
        {
            m_breakTime -= Time::DeltaTime();
        }
        else
        {
            float radian = float(rand() % 100) * 0.01f * TAU;
            Vec3 delta = Vec3(cosf(radian), 0, sinf(radian)) * m_moveDist;
            SetTargetXZCoord(m_initCoord + delta);
            m_breakTime = 0.35f;
        }
    }

    Vec3 xzPos = transform->position;
    xzPos.y = 0;

    Vec3 xzRel = m_targetXZCoord - xzPos;
    xzRel.y = 0;
    float xzDist = xzRel.magnitude();

    if (Vec3::Distance(Player::GetInstance()->transform->position, transform->position) < 5.0f)
    {
        m_run = true;

        Vec3 dir = transform->position - Player::GetInstance()->transform->position;
        dir.Normalize();
        SetTargetXZCoord(transform->position + dir * 30);
    }

    if (!m_hasTargetCoord || xzDist < 0.1f)
    {
        m_hasTargetCoord = false;
        m_animator->PlayIdle();

        if (m_run)
        {
            gameObject->Destroy();
        }
    }
    else if (m_hasTargetCoord)
    {
        Vec3 xzDir = xzRel;
        xzDir.Normalize();

        Vec3 vel = xzDir * m_speed * (m_run ? m_runFactor : 1.0f);
        vel = ToSlopeVelocity(vel);
        transform->position += vel * Time::DeltaTime();

        transform->forward = xzDir;

        m_animator->PlayWalk();
    }

    PhysicsRay ray(transform->position + Vec3::up() * m_radius, Vec3::down(), 50.0f);
    RaycastHit hit;
    if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider))
    {
        if (Vec3::Distance(hit.point, transform->position) < m_radius)
        {
            transform->position = hit.point + Vec3::up() * m_radius;
        }
    }
}

void ObjectRat::OnDestroy()
{
    if (m_quad)
    {
        m_quad->ReleaseUnmanaged();
        m_quad = nullptr;
    }
}

Vec3 ObjectRat::ToSlopeVelocity(const Vec3& velocity, float rayLength) const
{
    if (velocity.sqrMagnitude() > 0)
    {
        PhysicsRay ray;
        ray.point = transform->position + Vec3::up() * m_radius;
        ray.direction = Vec3::down();
        ray.distance = rayLength;
        RaycastHit hit;
        bool hasGround = Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider);

        if (hasGround)
        {
            Quat q = Quat::FromToRotation(Vec3::up(), hit.normal);
            return q * velocity;
        }
        else
        {
            return velocity;
        }
    }

    return Vec3::zero();
}

float ObjectRat::AngleToPlayer() const
{
    const Vec3& playerPos = Player::GetInstance()->transform->position;
    const Vec3& monsterPos = transform->position;

    Vec3 monsterToPlayer = playerPos - monsterPos;
    monsterToPlayer.y = 0;
    monsterToPlayer.Normalize();

    Vec3 monsterForward = transform->forward;
    monsterForward.y = 0;
    monsterForward.Normalize();

    return Vec3::Angle(monsterToPlayer, monsterForward);
}

float ObjectRat::AngleToPlayerWithSign() const
{
    const Vec3& playerPos = Camera::GetMainCamera()->transform->position;
    const Vec3& monsterPos = transform->position;

    Vec3 monsterToPlayer = playerPos - monsterPos;
    monsterToPlayer.y = 0;
    monsterToPlayer.Normalize();

    Vec3 monsterForward = transform->forward;
    monsterForward.y = 0;
    monsterForward.Normalize();

    float unsignedAngle = Vec3::Angle(monsterToPlayer, monsterForward);

    Vec2 monsterXZForward = Vec2(monsterForward.x, monsterForward.z);
    Vec2 XZMonsterToPlayer = Vec2(monsterToPlayer.x, monsterToPlayer.z);
    float z = Vec2::Cross(monsterXZForward, XZMonsterToPlayer).z;

    if (z > 0) return unsignedAngle * -1;
    else return unsignedAngle;
}

void ObjectRat::SetTargetXZCoord(const Vec3& point)
{
    Vec3 xzPoint = point;
    xzPoint.y = 0;

    m_targetXZCoord = xzPoint;

    m_hasTargetCoord = true;
}
