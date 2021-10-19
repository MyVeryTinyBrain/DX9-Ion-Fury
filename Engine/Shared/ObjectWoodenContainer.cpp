#include "shared_stdafx.h"
#include "ObjectWoodenContainer.h"
#include "Cube.h"

void ObjectWoodenContainer::Awake()
{
	{
		auto colliderObj = CreateGameObjectToChild(transform);
		colliderObj->transform->localEulerAngle = Vec3(0, 0, 0);
		auto body = colliderObj->AddComponent<Rigidbody>();
		auto collider = colliderObj->AddComponent<RightTriangleCollider>();
		body->isKinematic = true;
		collider->friction = 1.0f;
		collider->restitution = 1.0f;

	}

	{
		auto obj = CreateGameObjectToChild(transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, -1.5f, 0);
		obj->transform->localScale = Vec3(2.f, 2.f,2.f);

		
	}
}
