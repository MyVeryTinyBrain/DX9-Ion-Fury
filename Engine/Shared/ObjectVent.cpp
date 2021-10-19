#include "shared_stdafx.h"
#include "ObjectVent.h"
#include "Cube.h"

void ObjectVent::Awake()
{
	//{
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//}

	{
		auto colliderObj = CreateGameObjectToChild(transform);
		colliderObj->transform->localEulerAngle = Vec3(0, -90, 0);
		auto body = colliderObj->AddComponent<Rigidbody>();
		auto collider = colliderObj->AddComponent<RightTriangleCollider>();
		body->isKinematic = true;
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

	//{
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	debugRendererObj->transform->localEulerAngle = Vec3(0, -90, 0);
	//	auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
	//}

	{
		auto obj = CreateGameObjectToChild(transform);
		obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 1.f, 0);
		obj->transform->localScale = Vec3(2, 4.f, 0.4f);
		
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 2.9f, -0.5f);
		obj->transform->localScale = Vec3(2, 0.2f, 1.f);
		m_target = obj;
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, -0.7f, -0.5f);
		obj->transform->localScale = Vec3(2, 0.2f, 1.f);
		m_target = obj;
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(-0.9f, 1.f, -0.5f);
		obj->transform->localScale = Vec3(0.2f, 4.f, 1.f);
		m_target = obj;
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0.9f, 1.f, -0.5f);
		obj->transform->localScale = Vec3(0.2f, 4.f, 1.f);
		m_target = obj;
	}
}

void ObjectVent::Update()
{
	if (Input::GetKey(Key::Left))
		m_target->transform->position += Vec3( -0.1f, 0, 0);
	if (Input::GetKey(Key::Right))
		m_target->transform->position += Vec3(+0.1f, 0, 0);
	if (Input::GetKey(Key::Up))
		m_target->transform->position += Vec3(0, 0, +0.1f);
	if (Input::GetKey(Key::Down))
		m_target->transform->position += Vec3(0, 0, -0.1f);
}
