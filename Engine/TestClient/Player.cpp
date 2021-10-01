#include "stdafx.h"
#include "Player.h"

void Player::Awake()
{
	m_sphere = CreateGameObject();
	m_leftArm1 = CreateGameObject();
	m_leftArm2 = CreateGameObject();
	m_rightArm1 = CreateGameObject();
	m_rightArm2 = CreateGameObject();

	m_sphere->transform->parent = this->transform;
	m_leftArm1->transform->parent = this->transform;
	m_leftArm2->transform->parent = m_leftArm1->transform;
	m_rightArm1->transform->parent = this->transform;
	m_rightArm2->transform->parent = m_rightArm1->transform;

	m_sphere->transform->localPosition = Vec3::zero();
	m_sphere->transform->scale = Vec3(2, 2, 2);
	{
		auto renderer = m_sphere->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/SphereUserMesh.mesh");
		renderer->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());
		m_renderers[0] = renderer;
	}

	m_leftArm1->transform->localPosition = Vec3(-2, 0, 0);
	m_leftArm1->transform->scale = Vec3(2, 1, 1);
	{
		auto renderer = m_leftArm1->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
		renderer->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());
		m_renderers[1] = renderer;
	}

	m_leftArm2->transform->localPosition = Vec3(-1.5f, 2.0f, 0) * 0.5f;
	m_leftArm2->transform->localEulerAngle = Vec3(0, 0, 90);
	{
		auto renderer = m_leftArm2->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
		renderer->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());
		m_renderers[2] = renderer;
	}

	m_rightArm1->transform->localPosition = Vec3(+2, 0, 0);
	m_rightArm1->transform->scale = Vec3(2, 1, 1);
	{
		auto renderer = m_rightArm1->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
		renderer->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());
		m_renderers[3] = renderer;
	}

	m_rightArm2->transform->localPosition = Vec3(+1.5f, 2.0f, 0) * 0.5f;
	m_rightArm2->transform->localEulerAngle = Vec3(0, 0, 90);
	{
		auto renderer = m_rightArm2->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
		renderer->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());
		m_renderers[4] = renderer;
	}
}

void Player::Update()
{
	if (Input::GetKeyDown(Key::RightMouse))
	{
		for (auto& renderer : m_renderers)
		{
			Vec3 hit;
			Vec3 rayPoint, rayDir;
			Input::GetMouseWorldRay(rayPoint, rayDir);
			if (renderer->Raycast(hit, rayPoint, rayDir))
			{
				wcout << L"hit: " << gameObject->name << endl;
			}
		}
	}
}

void Player::SetArmLocalAngle(float angle)
{
	m_leftArm1->transform->localEulerAngle = Vec3(angle, 0, 0);
	m_rightArm1->transform->localEulerAngle = Vec3(angle, 0, 0);
}
