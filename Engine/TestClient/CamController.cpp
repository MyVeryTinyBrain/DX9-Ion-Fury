#include "stdafx.h"
#include "CamController.h"

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

	if (Input::GetKeyDown(Key::LeftMouse))
	{
		MoveMouseToCenterPos();
	}

	if (Input::GetKey(Key::LeftMouse))
	{
		float sensitivity = 0.5f;

		POINT prevPos = GetMousePointInClient();
		MoveMouseToCenterPos();
		POINT centerPos = GetMousePointInClient();
		Vec3 delta = Vec3(centerPos.y - prevPos.y, centerPos.x - prevPos.x, 0);
		ang -= delta * sensitivity;
	}

	transform->position = pos;
	transform->eulerAngle = ang;

	if (Input::GetKeyDown(Key::Space))
	{
		OnSpace(L"hello");
	}

	if (Input::GetKeyDown(Key::RightMouse))
	{
		float scale = 1.0f;
		GameObject* dynamic = CreateGameObject();
		dynamic->transform->position = transform->position;
		auto body = dynamic->AddComponent<Rigidbody>();
		body->SetLinearVelocity(transform->forward * 15);
		//dynamic->AddComponent<BoxCollider>()->extents = Vec3::one() * scale;
		dynamic->AddComponent<SphereCollider>()->radius = scale;
		auto renderer = dynamic->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
	}
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
	POINT center = { rect.right * 0.5f, rect.bottom * 0.5f };
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
