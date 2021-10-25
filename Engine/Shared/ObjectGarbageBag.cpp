#include "shared_stdafx.h"
#include "ObjectGarbageBag.h"
#include "PhysicsLayers.h"

#include "ItemHealthPack.h"
#include "ItemArmor.h"
#include "ItemRevolverAmmo.h"
#include "ItemShotgunAmmo.h"
#include "ItemSMGAmmo.h"
#include "ItemLauncherAmmo.h"
#include "ItemChaingunAmmo.h"
#include "ItemBowAmmo.h"

void ObjectGarbageBag::Awake()
{
    Monster::Awake();

    m_hp = m_maxHP;

    m_body->sleepThresholder = 2.0f;

    m_texture[2] = Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan/trashcan0.png");
    m_texture[1] = Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan/trashcan1.png");
    m_texture[0] = Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan/trashcan2.png");

    m_rendererObj->transform->localScale = Vec3::one() * 2.0f;
    m_rendererObj->transform->localPosition = Vec3(0, -0.1f, 0);
    m_rendererObj->transform->localPosition = Vec3::zero();

    m_renderer = CreateRenderer();
    m_renderer->gameObject->transform->localPosition = Vec3(0, 0, 0);
    m_renderer->SetTexture(0, m_texture[2]);
}

void ObjectGarbageBag::Update()
{
    Monster::Update();

    float percent = m_hp / m_maxHP;
    percent = Clamp(percent, 0, 1);
    float fIndex = percent * 2.0f;
    int index = int(fIndex);

    m_renderer->SetTexture(0, m_texture[index]);
}

void ObjectGarbageBag::OnDestroy()
{
    Monster::OnDestroy();

    m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &ObjectGarbageBag::OnCollisionEnter);
}

void ObjectGarbageBag::OnCollisionEnter(const CollisionEnter& collision)
{
    m_body->isKinematic = true;
}

Collider* ObjectGarbageBag::InitializeCollider(GameObject* colliderObj)
{
    if(Time::DeltaTime() == 0)
    {
        auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
        renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
    }

    m_collider = colliderObj->AddComponent<SphereCollider>();
    m_collider->SetIgnoreLayer((uint8_t)PhysicsLayers::Player, true);
    m_collider->SetIgnoreLayer((uint8_t)PhysicsLayers::Monster, true);
    m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &ObjectGarbageBag::OnCollisionEnter);

    return m_collider;
}

void ObjectGarbageBag::OnDamage(DamageParameters& params)
{
}

void ObjectGarbageBag::OnDead(bool& dead, DamageParameters& params)
{
    int itemIndex = rand() % 5;

    GameObject* itemObj = CreateGameObject();
    itemObj->transform->position = transform->position;

    Item* item = nullptr;

    switch (itemIndex)
    {
        case 0:
            item = itemObj->AddComponent<ItemHealthPack>();
            break;
        case 1:
            item = itemObj->AddComponent<ItemArmor>();
            break;
        case 2:
            item = itemObj->AddComponent<ItemRevolverAmmo>();
            break;
        case 3:
            item = itemObj->AddComponent<ItemShotgunAmmo>();
            break;
        case 4:
            item = itemObj->AddComponent<ItemSMGAmmo>();
            break;
        case 5:
            item = itemObj->AddComponent<ItemLauncherAmmo>();
            break;
        case 6:
            item = itemObj->AddComponent<ItemChaingunAmmo>();
            break;
        case 7:
            item = itemObj->AddComponent<ItemBowAmmo>();
            break;
    }

    if (!item)
    {
        itemObj->Destroy();
    }
    else
    {
        item->ResetHeight();
    }

    gameObject->Destroy();
}
