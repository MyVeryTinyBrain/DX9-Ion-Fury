#include "shared_stdafx.h"
#include "Objectelevator.h"
#include "Player.h"
#include "ObjectButton.h"

void Objectelevator::Awake()
{
	{
		auto debugRendererObj = CreateGameObjectToChild(transform);
		auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}


	m_root = CreateGameObjectToChild(transform);

	{
		auto body = m_root->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = m_root->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

	m_leftdoor = CreateGameObjectToChild(m_root->transform);
	m_leftdoor->transform->localScale = Vec3(0.5f, 0.7f, 0.1f);
	m_leftdoor->transform->localEulerAngle = Vec3(90.f, 0.0f, 0.f);
	m_leftdoor->transform->localPosition = Vec3(0.25f, 0.5f, 4.5f);
	leftfirstlocalpositon = m_leftdoor->transform->localPosition;
	{
		auto renderer = m_leftdoor->AddComponent<UserMeshRenderer>();
		//renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}

	{
		auto body = m_leftdoor->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = m_leftdoor->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

	m_rightdoor = CreateGameObjectToChild(m_root->transform);
	m_rightdoor->transform->localScale = Vec3(0.5f, 0.7f, 0.1f);
	m_rightdoor->transform->localEulerAngle = Vec3(90.f, 0.0f, 0.f);
	m_rightdoor->transform->localPosition = Vec3(-0.25f, 0.5f, 4.5f);// ÁÂ¿ì /z y  //-0.33
	rightfirstlocalpositon = m_rightdoor->transform->localPosition;
	{
		auto renderer = m_rightdoor->AddComponent<UserMeshRenderer>();
		//renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentBlueTexture));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}

	{
		auto body = m_rightdoor->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = m_rightdoor->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}



}

void Objectelevator::Update()
{
	if (Input::GetKey(Key::G))
	{
		opendoor = true;
		closedoor = false;
	}

	if (Input::GetKey(Key::F))
	{
		opendoor = false;
		closedoor = true;

	}

	ElevatorDoorControl();
}

void Objectelevator::SetGoUpElevator()
{
	GoUpElevator = true;
	GoDownElevator = false;
}

void Objectelevator::SetGoDownElevator()
{
	GoUpElevator = false;
	GoDownElevator = true;
}
bool Objectelevator::GetUpElevator()
{
	return GoUpElevator;
}
bool Objectelevator::GetDownElevator()
{
	return GoDownElevator;
}

void Objectelevator::SetFloor(int _floor)
{
	m_Floor = _floor;
}

int Objectelevator::GetCurrentFloor()
{
	return m_Floor;
}

void Objectelevator::ElevatorDoorControl()
{

	if (opendoor) // ¿­¸®´Â°Å
	{
		m_leftdoor->transform->localPosition += Vec3(0.1f, 0, 0) * Time::DeltaTime();
		m_rightdoor->transform->localPosition -= Vec3(0.1f, 0, 0) * Time::DeltaTime();


		if (m_leftdoor->transform->localPosition.x >= 0.6f)
		{
			opendoor = false;
			closedoor = true;
		}
	}

	if (closedoor) //´ÝÈ÷´Â°Å
	{
		m_leftdoor->transform->localPosition -= Vec3(0.1f, 0, 0) * Time::DeltaTime();
		m_rightdoor->transform->localPosition += Vec3(0.1f, 0, 0) * Time::DeltaTime();

		if (m_leftdoor->transform->localPosition.x <= 0.25f)
		{
			closedoor = false;
			return;
		}
	}
}

void Objectelevator::OnUse()
{
}


