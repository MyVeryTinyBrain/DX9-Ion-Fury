#include "IonFuryEditorBase.h"
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"

void FreePerspectiveCamera::Update()
{
	Vec3 pos = transform->position;
	Vec3 ang = transform->eulerAngle;

	float acceleration = Input::GetKey(Key::LShift) ? m_accelerateFactor : 1.0f;

	if (Input::GetKey(Key::A))
		pos += -transform->right * m_linearSpeed * acceleration * Time::DeltaTime();
	if (Input::GetKey(Key::D))
		pos += transform->right * m_linearSpeed * acceleration * Time::DeltaTime();
	if (Input::GetKey(Key::W))
		pos += transform->forward * m_linearSpeed * acceleration * Time::DeltaTime();
	if (Input::GetKey(Key::S))
		pos += -transform->forward * m_linearSpeed * acceleration * Time::DeltaTime();
	
	if (Input::GetKey(Key::P))
		AddObject();

	if (Input::GetKey(Key::Left))
		ang.y -= m_angularSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Right))
		ang.y += m_angularSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Up))
		ang.x -= m_angularSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Down))
		ang.x += m_angularSpeed * Time::DeltaTime();
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
		Vec3 delta = Vec3(centerPos.y - prevPos.y, centerPos.x - prevPos.x, 0);
		ang -= delta * sensitivity;
	}

	transform->position = pos;
	transform->eulerAngle = ang;
}

void FreePerspectiveCamera::MoveMouseToCenterPos()
{
	RECT rect;
	GetClientRect(GraphicDevice::GetInstance()->GetWindowHandle(), &rect);
	POINT center = { rect.right * 0.5f, rect.bottom * 0.5f };
	ClientToScreen(GraphicDevice::GetInstance()->GetWindowHandle(), &center);
	SetCursorPos(center.x, center.y);
}

POINT FreePerspectiveCamera::GetMousePointInClient() const
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GraphicDevice::GetInstance()->GetWindowHandle(), &pos);
	return pos;
}

void FreePerspectiveCamera::AddObject()
{
	GameObject* Obj = CreateGameObject();
	Obj->AddComponent<Gizmo>();
	Obj->transform->position = transform->position + transform->forward * 2;
	auto Renderer = Obj->AddComponent<UserMeshRenderer>();
	Renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
	Renderer->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());
}
