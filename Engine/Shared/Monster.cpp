#include "shared_stdafx.h"
#include "Monster.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "FPSCharacterController.h"

void Monster::Awake()
{
	m_body = gameObject->AddComponent<Rigidbody>();
    m_body->SetRotationLockAxis(PhysicsAxis::All, true);
    m_refBody = m_body;

	m_colliderObj = CreateGameObjectToChild(transform);
	m_collider = InitializeCollider(m_colliderObj);
	if (m_collider)
	{
		m_collider->layerIndex = (uint8_t)PhysicsLayers::Monster;
        m_collider->friction = 1.0f;
	}

    MaterialParameters params;
    params.alphaTest = true;
    params.renderQueue = RenderQueue::AlphaTest;
    m_material = Material::CreateUnmanaged(params);

    m_rendererObj = CreateGameObjectToChild(transform);
    m_rendererObj->transform->localPosition = Vec3(0, -1.0f, 0);

    m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
}

void Monster::FixedUpdate()
{
}

void Monster::Update()
{
    LightMateriaProcessing();
}

void Monster::LateUpdate()
{
}

void Monster::OnDestroy()
{
    m_material->ReleaseUnmanaged();
    m_quad->ReleaseUnmanaged();
}

Vec3 Monster::ToSlopeVelocity(const Vec3& velocity, float rayLength) const
{
    if (velocity.sqrMagnitude() > 0)
    {
        PhysicsRay ray;
        ray.point = m_collider->transform->position;
        ray.direction = Vec3::down();
        ray.distance = rayLength;
        RaycastHit hit;
        bool hasGround = Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider, m_body);

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

void Monster::TakeDamage(const DamageParameters& params)
{
    if (m_isDead)
    {
        return;
    }

    DamageParameters copiedParams = params;

    OnDamage(copiedParams);

    float damage = Clamp(copiedParams.damage, 0, FLT_MAX);

    if (damage > 0)
    {
        m_damageEffectCounter = DAMAGE_EFFECT_DURATION;
    }

    m_hp -= damage;
    
    if (m_refBody && !m_refBody->isKinematic)
    {
        m_body->AddForce(copiedParams.force, ForceMode::Impulse);
    }

    if (m_hp <= 0 && !m_isDead)
    {
        m_isDead = true;
        OnDead(m_isDead, copiedParams);
    }

    if (m_isDead)
    {
        // 몬스터가 사망하면 몬스터가 다른 몬스터 또는 플레이어와 충돌하지 않아야 합니다.
        // 또한 쿼리에 포함되면 안됩니다.
        // 따라서 지형과만 충돌하는 레이어로 변경합니다.
        m_collider->layerIndex = (uint8_t)PhysicsLayers::MonsterDeadBody;

        if (m_refBody && !m_refBody->isKinematic)
        {
            m_body->velocity = Vec3(0, m_body->velocity.y, 0);
            m_body->ClearForce(ForceMode::Impulse);
            m_body->ClearForce(ForceMode::Force);
            m_body->ClearForce(ForceMode::Acceleration);
        }
    }
}

float Monster::AngleToPlayer() const
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

float Monster::AngleToPlayerWithSign() const
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

float Monster::GetHP() const
{
	return m_hp;
}

void Monster::SetHP(float value)
{
	m_hp = value;
}

float Monster::GetMoveSpeed() const
{
	return m_moveSpeed;
}

void Monster::SetMoveSpeed(float value)
{
	m_moveSpeed = value;
}

bool Monster::IsDead() const
{
    return m_isDead;
}

void Monster::LightMateriaProcessing()
{
    float percent = m_damageEffectCounter / DAMAGE_EFFECT_DURATION;

    if (percent <= 0)
    {
        m_material->params.ambient = m_defaultLightColor;
        m_material->params.diffuse = m_defaultLightColor;
        m_material->params.emissive = m_defaultEmissive;
        m_material->params.specular = Color::black();
    }
    else
    {
        float invPercent = 1.0f - percent;

        m_material->params.ambient = m_defaultLightColor * invPercent;
        m_material->params.diffuse = m_defaultLightColor * invPercent;
        m_material->params.emissive = Color::Lerp(m_defaultEmissive, m_damageEffectColor, percent);
        m_material->params.specular = Color::black();
    }

    //if (percent <= 0)
    //{
    //    m_material->params.ambient = Color::white();
    //    m_material->params.diffuse = Color::white();
    //    m_material->params.emissive = m_defaultEmissive;
    //    m_material->params.specular = Color::black();
    //}
    //else
    //{
    //    m_material->params.ambient = Color::black();
    //    m_material->params.diffuse = Color::black();
    //    m_material->params.emissive = m_damageEffectColor;
    //    m_material->params.specular = Color::black();
    //}

    m_damageEffectCounter -= Time::DeltaTime();
}

UserMeshBillboardRenderer* Monster::CreateRenderer()
{
    auto rendererChildObj = CreateGameObjectToChild(m_rendererObj->transform);
    rendererChildObj->transform->localPosition = Vec3(0, 0.5f, 0);

    auto renderer = rendererChildObj->AddComponent<UserMeshBillboardRenderer>();
    renderer->freezeX = true;
    renderer->freezeZ = true;
    renderer->material = m_material;
    renderer->userMesh = m_quad;

    m_renderers.push_back(renderer);

    return renderer;
}
