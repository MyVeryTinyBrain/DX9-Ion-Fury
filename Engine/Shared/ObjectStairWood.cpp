#include "shared_stdafx.h"
#include "ObjectStairWood.h"
#include "Cube.h"

void ObjectStairWood::Awake()
{
	//{
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//}

	auto root = CreateGameObjectToChild(transform);
	root->transform->localScale = Vec3(2, 2, 2);

	{
		auto colliderObj = CreateGameObjectToChild(root->transform);
		colliderObj->transform->localEulerAngle = Vec3(0, -90, 0);
		auto body = colliderObj->AddComponent<Rigidbody>();
		auto collider = colliderObj->AddComponent<RightTriangleCollider>();
		body->isKinematic = true;
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

	//{
	//	auto debugRendererObj = CreateGameObjectToChild(root->transform);
	//	debugRendererObj->transform->localEulerAngle = Vec3(0, -90, 0);
	//	auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
	//}

	auto SetTexture = [&](Cube* cube)
	{
		cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/map/34.png"));
		cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/map/34.png"));
		cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/map/8.png"));
		cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/map/8.png"));
		cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/map/8.png"));
		cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/map/8.png"));
	};

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, -0.4f, 0);
		obj->transform->localScale = Vec3(1, 0.2f, 1);

		SetTexture(cube);
	}

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, -0.2f, 0.1f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.8f);

		SetTexture(cube);
	}

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 0.0f, 0.2f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.6f);

		SetTexture(cube);
	}

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 0.2f, 0.3f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.4f);

		SetTexture(cube);
	}

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 0.4f, 0.4f);
		obj->transform->localScale = Vec3(1, 0.2f, 0.2f);

		SetTexture(cube);
	}
}