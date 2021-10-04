#include "stdafx.h"
#include "CamController.h"
#include "../Engine/header/PhysicsQuery.h"

void CamController::Awake()
{
	OnSpace += Function<void(const wstring&)>(this, &CamController::Func);
	OnSpace += Function<void(const wstring&)>(this, &CamController::Func2);
}

void CamController::Update()
{
	float linSpeed = 2;
	float angSpeed = 45;

	Vec3 pos = transform->position;
	Vec3 ang = transform->eulerAngle;

	if (Input::GetKey(Key::A))
		pos += -transform->right * linSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::D))
		pos += transform->right * linSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::W))
		pos += transform->forward * linSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::S))
		pos += -transform->forward * linSpeed * Time::DeltaTime();

	if (Input::GetKey(Key::Left))
		ang.y -= angSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Right))
		ang.y += angSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Up))
		ang.x -= angSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Down))
		ang.x += angSpeed * Time::DeltaTime();
	ang.z = 0;

	if (Input::GetKeyDown(Key::RightMouse))
	{
		MoveMouseToCenterPos();
	}

	if (Input::GetKey(Key::RightMouse))
	{
		float sensitivity = 0.5f;

		POINT prevPos = GetMousePointInClient();
		MoveMouseToCenterPos();
		POINT centerPos = GetMousePointInClient();
		Vec3 delta = Vec3(float(centerPos.y - prevPos.y), float(centerPos.x - prevPos.x), 0);
		ang -= delta * sensitivity;
	}

	// angle lock
	ang.x = MathEx::Clamp(ang.x, -90, +90);
	ang.z = MathEx::Clamp(ang.z, -90, +90);

	transform->position = pos;
	transform->eulerAngle = ang;

	if (Input::GetKeyDown(Key::LeftMouse))
	{
		Vec3 rayPoint, rayDir;
		Input::GetMouseWorldRay(rayPoint, rayDir);

		GameObject* obj = CreateGameObject();
		Collider* col = nullptr;
		auto r = obj->AddComponent<UserMeshRenderer>();
		r->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
		int n = rand() % 5;
		switch (n)
		{
			case 0: 
				col = obj->AddComponent<BoxCollider>(); 
				r->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
				break;
			case 1: 
				col = obj->AddComponent<SphereCollider>(); 
				r->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
				break;
			case 2:
				col = obj->AddComponent<CapsuleCollider>();
				r->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
				break;
			case 3:
				col = obj->AddComponent<RightTriangleCollider>();
				r->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
				break;
			case 4:
				col = obj->AddComponent<TriangleCollider>();
				r->userMesh = Resource::FindAs<UserMesh>(BuiltInTriangleUserMesh);
				break;
		}
		auto body = obj->AddComponent<Rigidbody>();
		body->SetVelocity(rayDir * 15);
		
		obj->transform->position = transform->position;
		obj->transform->rotation = transform->rotation;
		obj->transform->scale = Vec3::one() * (float(rand() % 100 + 1) * 0.01f + 0.5f);
	}

	if (Input::GetKeyDown(Key::Space))
	{

	}
}

void CamController::Render()
{

}

void CamController::Func(const wstring& msg)
{
	wcout << msg << endl;
}

void CamController::Func2(const wstring& msg)
{
	wcout << L"2: " << msg << endl;
}

void CamController::MoveMouseToCenterPos()
{
	RECT rect;
	GetClientRect(GraphicDevice::GetInstance()->GetWindowHandle(), &rect);
	POINT center = { LONG(rect.right * 0.5f), LONG(rect.bottom * 0.5f) };
	ClientToScreen(GraphicDevice::GetInstance()->GetWindowHandle(), &center);
	SetCursorPos(center.x, center.y);
}

POINT CamController::GetMousePointInClient() const
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GraphicDevice::GetInstance()->GetWindowHandle(), &pos);
	return pos;
}
