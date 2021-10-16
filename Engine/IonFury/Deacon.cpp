#include "stdafx.h"
#include "Deacon.h"
#include "DeaconSpriteAnimator.h"
#include "PhysicsInitialize.h"
#include "Player.h"

void Deacon::Awake()
{
    Monster::Awake();

    m_hp = 5;
    m_moveSpeed = 2.f;

    m_body->mass = 1.f;
    //����

    m_body->interpolate = true;
    // ����

    m_body->useGravity = false;
    // �߷�

    m_body->sleepThresholder = 1.f;
    //���� ���� ��ȯ�� �� �ֽ��ϴ�. Rigidbody�� ���ڱ� ������ �� �����Ӹ��� ������Ʈ���� �����Ƿ� ���ҽ� ���������� �ʽ��ϴ�. ������ٵ��� � �������� �������� ���� ���� �� �Ӱ谪���� ������ ���� �ĺ��Դϴ�.

    m_rendererObj->transform->scale = Vec3::one() * 10.0f;

    m_rendererObj->transform->localPosition = Vec3(0, -0.5f, 0);
  
    m_renderer->freezeX = false;
    m_renderer->freezeZ = false;
    //������ 

    m_animator = m_rendererChildObj->AddComponent<DeaconSpriteAnimator>();

}

void Deacon::FixedUpdate()
{
    //���� ������Ʈ 
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
}

void Deacon::OnDestroy()
{
    Monster::OnDestroy();
}

Collider* Deacon::InitializeCollider(GameObject* colliderObj)
{
    {
        auto renderer = colliderObj->AddComponent < UserMeshRenderer >();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh); //�Ǹ��� ����ص������ʳ�!? �����!?
        renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
        renderer->material = Resource::FindAs <Material > (BuiltInNolightTransparentMaterial);
    }
    return nullptr;
}

void Deacon::OnDamage(DamageParameters& params)
{
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
}

void Deacon::Explosion()
{
}

void Deacon::Moving(MovingType type)
{
}
