#include "shared_stdafx.h"
#include "ObjectVent.h"
#include "Cube.h"
#include "RenderLayers.h"


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
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 2.f, 0);
		obj->transform->localScale = Vec3(2, 4.f, 1.f);

		cube->SetMaterials(Resource::FindAs<Material>(BuiltInAlphaTestMaterial));
		cube->SetRenderLayers((int)RenderLayers::Generic);

		cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
		cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
		cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
		cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
		cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_front0.png"));
		cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_back.png"));
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 4.f, 1.0f);
		obj->transform->localScale = Vec3(2, 0.2f, 1.f);
		m_target = obj;

		//cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(0, 0.f, 1.0f);
		obj->transform->localScale = Vec3(2, 0.2f, 1.f);
		
		//cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(-1.1f, 2.f, 1.0f);
		obj->transform->localScale = Vec3(0.2f, 4.f, 1.f);
		
	//	cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
	}
	{
		auto obj = CreateGameObjectToChild(transform);
		auto cube = obj->AddComponent<Cube>();
		obj->transform->localPosition = Vec3(1.1f, 2.f, 1.0f);
		obj->transform->localScale = Vec3(0.2f, 4.f, 1.f);
	
		//cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/Vent_side.png"));
	}
}

void ObjectVent::Update()
{
	if (Input::GetKey(Key::Left))
		m_target->transform->localPosition += Vec3( -1.f, 0, 0);
	if (Input::GetKey(Key::Right))
		m_target->transform->localPosition += Vec3(+1.f, 0, 0);
	if (Input::GetKey(Key::Up))
		m_target->transform->localPosition += Vec3(0, 0, 1.f);
	if (Input::GetKey(Key::Down))
		m_target->transform->localPosition += Vec3(0, 0, -1.f);
}
