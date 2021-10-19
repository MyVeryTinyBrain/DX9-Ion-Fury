#include "shared_stdafx.h"
#include "ObjectGetItem.h"
#include "Cube.h"
#include "RenderLayers.h"
#include "UserMeshBillboardRenderer.h"
#include "Player.h"
#include "SpriteAnimation.h"

void ObjectGetItem::Awake()
{
	m_hitCount = 10;

	{
		auto colliderObj = CreateGameObjectToChild(transform);
		colliderObj->transform->localEulerAngle = Vec3(0, 0, 0);
		auto body = colliderObj->AddComponent<Rigidbody>();
		auto collider = colliderObj->AddComponent<RightTriangleCollider>();
		body->isKinematic = true;
		collider->friction = 1.0f;
		collider->restitution = 1.0f;

	}

}

void ObjectGetItem::Update()
{
	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& gunnerPos = transform->position;
	Vec3 forward = playerPos - gunnerPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	if (m_hitCount < 9)
	{
		int i = 0;
		//m_texture = Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan0.png");
	}
	else if (m_hitCount <=1)
	{
		//m_texture = Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan1.png");

	}
	else
	{
		//m_texture = Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan2.png");

	}
}
