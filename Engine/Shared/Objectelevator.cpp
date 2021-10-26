#include "shared_stdafx.h"
#include "Objectelevator.h"
#include "Player.h"
#include "ObjectButton.h"
#include "Trigger.h"


void Objectelevator::Awake()
{

	{
		auto debugRendererObj = CreateGameObjectToChild(transform);
		auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/seongyeonfile/Tile34.png"));

		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}


	m_root = this->GetGameObject();

	{
		auto body = m_root->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = m_root->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

	m_leftdoor = CreateGameObjectToChild(m_root->transform);
	m_leftdoor->transform->localScale = Vec3(0.5f, 0.7f, 0.1f);
	m_leftdoor->transform->localEulerAngle = Vec3(-90.f, 0.0f, 0.f);
	m_leftdoor->transform->localPosition = Vec3(0.25f, 0.5f, 3.5f);
	leftfirstlocalpositon = m_leftdoor->transform->localPosition;
	{
		auto renderer = m_leftdoor->AddComponent<UserMeshRenderer>();
		//renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/seongyeonfile/Tile32.png"));

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
	m_rightdoor->transform->localPosition = Vec3(-0.25f, 0.5f, 3.5f);// 좌우 /z y  //-0.33

	rightfirstlocalpositon = m_rightdoor->transform->localPosition;
	{
		auto renderer = m_rightdoor->AddComponent<UserMeshRenderer>();
		//renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/seongyeonfile/Tile32.png"));

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

	Vec3 PlayerPos = Player::GetInstance()->transform->position; //		Vec3 targetCoord = Player::GetInstance()->transform->position;

	//if (Input::GetKey(Key::F))
	//{
	//	opendoor = false;
	//	closedoor = true;

	//}

	ElevatorDoorControl();
}

void Objectelevator::OnDisable()
{
}

void Objectelevator::SetGoUpElevator()
{
	MoveElevator = true;
}

void Objectelevator::SetGoDownElevator()
{
	MoveElevator = false;
}
bool Objectelevator::GetUpElevator()
{
	return MoveElevator;
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

	if (opendoor) // 열리는거
	{
		m_leftdoor->transform->localPosition += Vec3(0.1f, 0, 0) * Time::DeltaTime();
		m_rightdoor->transform->localPosition -= Vec3(0.1f, 0, 0) * Time::DeltaTime();

			closedt += Time::DeltaTime(); 
		if (m_leftdoor->transform->localPosition.x >= 0.6f)
		{
			opendoor = false;
			if(closedt>2.f)
				closedoor = true;
		}
	}

	if (closedoor)//닫히는거
	{
		m_leftdoor->transform->localPosition -= Vec3(0.1f, 0, 0) * Time::DeltaTime();
		m_rightdoor->transform->localPosition += Vec3(0.1f, 0, 0) * Time::DeltaTime();

		if (m_leftdoor->transform->localPosition.x <= 0.25f)
		{
			closedoor = false;
			if (m_2Floor)
				return;
			MoveElevator = true;
		}
	}

	if (MoveElevator && m_1Floor) //올라가는거 
	{
		cout << transform->position.y << endl;
		if (transform->position.y <= 9.6f)
		{
			transform->position += Vec3(0, 1.2f, 0) * Time::DeltaTime();
		}
		else
		{
			opendoor = true;
			MoveElevator = false;
			m_1Floor = false;
			m_2Floor = true;
		}
	}

	if (MoveElevator && m_2Floor)
	{
		if (transform->position.y >= 0.f)
		{
			transform->position -= Vec3(0, 1.2f, 0) * Time::DeltaTime();

		}
		else
		{
			MoveElevator = false;
			m_1Floor = true;
			m_2Floor = false;
		}
	}
}

void Objectelevator::OnUse(bool valid)
{
}


