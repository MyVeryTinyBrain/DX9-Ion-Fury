#include "stdafx.h"
#include "Gunner.h"
#include "GunnerSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"

void Gunner::Awake()
{
    Monster::Awake();

    m_hp = 10;
    m_moveSpeed = 3.0f;

    m_body->mass = 1.0f;
    m_body->interpolate = true;

    // �������Ǵ� ������ �������� Ű��ϴ�.
    m_rendererObj->transform->scale = Vec3::one() * 3.0f;

    m_animator = m_rendererChildObj->AddComponent<GunnerSpriteAnimator>();
}

void Gunner::FixedUpdate()
{
    Monster::FixedUpdate();

    // ��ǥ �������� �̵��ϴ� �����Դϴ�.
    MoveToTarget();

    // ������ forward ����� �÷��̾ �ٶ󺸴� ������ ����ؼ� �ִϸ����Ϳ� �����մϴ�.
    m_animator->SetAngle(AngleToPlayerWithSign());

    // ��ǥ ������ ���� ��쿡 ��ǥ ������ �����ϰ� �缳���մϴ�.
    if (!m_hasTargetCoord)
    {
        float randomRadian = (rand() % 360) * Deg2Rad;
        float randomDistance = (rand() % 15) + 2.1f + 0.1f;
        Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
        SetTargetCoord(targetCoord);
    }
}

void Gunner::Update()
{
    Monster::Update();

    // ���� �ӵ��� �����ӵ� �̻��̸� �ȴ� �ִϸ��̼��� ����մϴ�.
    // �ƴ϶�� ���� �ִϸ��̼��� ����մϴ�.

    if (m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
        m_animator->PlayWalk();
    else
        m_animator->PlayIdle();
}

void Gunner::OnDestroy()
{
    Monster::OnDestroy();
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

void Gunner::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
    switch (damageType)
    {
        case MonsterDamageType::Bullet:
        case MonsterDamageType::Explosion:
            m_animator->PlayDamage(GunnerSpriteAnimator::DAMAGE::DAMAGE_GENERIC);
            break;
        case MonsterDamageType::Zizizik:
            m_animator->PlayDamage(GunnerSpriteAnimator::DAMAGE::DAMAGE_ZIZIZIK);
            break;
    }

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& gunnerPos = transform->position;
    Vec3 forward = playerPos - gunnerPos;
    forward.y = 0;
    forward.Normalize();
    transform->forward = forward;
}

void Gunner::OnDead(bool& dead, MonsterDamageType damageType)
{
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
