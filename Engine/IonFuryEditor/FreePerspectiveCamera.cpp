#include "IonFuryEditorBase.h"
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"
#include "Pickable.h"
#include "EditorManager.h"
#include "LightObj.h"
#include "EditorEnum.h"


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

	if (Input::GetKeyDown(Key::O))
		EditorManager::GetInstance()->GetGizmo()->DeleteAttachedObject();


	if (Input::GetKey(Key::Left))
		ang.y -= m_angularSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Right))
		ang.y += m_angularSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Up))
		ang.x -= m_angularSpeed * Time::DeltaTime();
	if (Input::GetKey(Key::Down))
		ang.x += m_angularSpeed * Time::DeltaTime();
	ang.z = 0;

	// angle lock
	ang.x = MathEx::Clamp(ang.x, -90, +90);
	ang.z = MathEx::Clamp(ang.z, -90, +90);

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

	transform->position = pos;
	transform->eulerAngle = ang;
}

void FreePerspectiveCamera::MoveMouseToCenterPos()
{
	RECT rect;
	GetClientRect(GraphicDevice::GetInstance()->GetWindowHandle(), &rect);
	POINT center = { LONG(rect.right * 0.5f), LONG(rect.bottom * 0.5f) };
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

void FreePerspectiveCamera::Add_MapObject(bool ColliderExistence, Vec2 UVScale, COMBOBOX comboBox, const tag_t& tag, const wstring& ObjName, const wstring& localPathTexture)
{
	GameObject* Obj = CreateGameObject(tag);

	Obj->name = ObjName;

	Obj->transform->position = transform->position + transform->forward * 2;

	auto test = Obj->AddComponent<Pickable>();
	
	test->PushInVector(Type::Map);
	test->Settings(UVScale, comboBox, localPathTexture, ColliderExistence);
}

