#include "shared_stdafx.h"
#include "ObjectVent.h"
#include "Cube.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "FPSCharacterController.h"

void ObjectVent::Awake()
{
	auto body = gameObject->AddComponent<Rigidbody>();
	body->isKinematic = true;

	m_root = CreateGameObjectToChild(transform);

	{
		auto colliderObj = CreateGameObjectToChild(m_root->transform);

		//{
		//	auto debugRendererObj = CreateGameObjectToChild(colliderObj->transform);
		//	auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
		//	renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
		//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		//}

		auto collider = colliderObj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

	{
		auto colliderObj = CreateGameObjectToChild(m_root->transform);
		colliderObj->transform->localPosition = Vec3(0, 5.5f, 0);
		colliderObj->transform->localScale = Vec3(1, 10, 1);

		if (Time::DeltaTime() == 0)
		{
			auto debugRendererObj = CreateGameObjectToChild(colliderObj->transform);
			auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
			renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
			renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
			renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		}

		m_forceTrigger = colliderObj->AddComponent<BoxCollider>();
		m_forceTrigger->isTrigger = true;
		m_forceTrigger->layerIndex = (uint8_t)PhysicsLayers::Forcer;
	}

	{
		auto cubeObj = CreateGameObjectToChild(m_root->transform);
		Cube* cube = cubeObj->AddComponent<Cube>();

		cube->SetMaterials(Resource::FindAs<Material>(BuiltInCulloffGeometryMaterial));

		cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/side.png"));
		cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/side.png"));
		cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/side.png"));
		cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/side.png"));
		cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/side.png"));

		cube->top->material = Resource::FindAs<Material>(BuiltInAlphaTestMaterial);
		cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/frame.png"));
	}

	{
		m_fanObj = CreateGameObjectToChild(m_root->transform);
		m_fanObj->transform->localPosition = Vec3(0, 0.5f, 0);
		auto renderer = m_fanObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadTopUserMesh);
		renderer->material = Resource::FindAs<Material>(BuiltInAlphaTestMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/Vent/fan.png"));
	}
}

void ObjectVent::Update()
{
	if (Time::DeltaTime() == 0)
	{
		return;
	}

	if (!m_spin)
	{
		return;
	}

	m_fanObj->transform->localEulerAngle -= Vec3(0, 360, 0) * Time::DeltaTime() * 3;

	Collider* collider = Physics::OverlapCollider(m_forceTrigger, 1 << (uint8_t)PhysicsLayers::Player, PhysicsQueryType::Collider);

	if (collider)
	{
		//Player::GetInstance()->transform->position -= transform->forward * Time::DeltaTime() * 10.0f;
		Player::GetInstance()->rigidbody->AddForce(transform->up * 10, ForceMode::Force);
	}
}
