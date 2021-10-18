#include "stdafx.h"
#include "ObjectStair.h"

void ObjectStair::Awake()
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
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		obj->transform->localPosition = Vec3(0, -0.4f, 0);
		obj->transform->localScale = Vec3(1, 0.2f, 1);
	}

	{
		auto obj = CreateGameObjectToChild(transform);
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		obj->transform->localPosition = Vec3(0, -0.2f, 0.1f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.8f);
	}

	{
		auto obj = CreateGameObjectToChild(transform);
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		obj->transform->localPosition = Vec3(0, 0.0f, 0.2f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.6f);
	}

	{
		auto obj = CreateGameObjectToChild(transform);
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		obj->transform->localPosition = Vec3(0, 0.2f, 0.3f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.4f);
	}

	{
		auto obj = CreateGameObjectToChild(transform);
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		obj->transform->localPosition = Vec3(0, 0.4f, 0.4f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.2f);
	}
}
