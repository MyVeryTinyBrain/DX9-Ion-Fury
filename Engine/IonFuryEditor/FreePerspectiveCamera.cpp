#include "IonFuryEditorBase.h"
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"
#include "Pickable.h"
#include "HandlingObject.h"
#include "EditorManager.h"
#include "LightObj.h"
#include "EditorEnum.h"
#include <string>


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

	//if (Input::GetKeyDown(Key::O))
	//	EditorManager::GetInstance()->GetGizmo()->DeleteAttachedObject();


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

Pickable* FreePerspectiveCamera::Add_MapObject(bool ColliderExistence, Vec3 Size, Vec3 Rotation, Vec2 UVScale, COMBOBOX comboBox, const tag_t& tag, const wstring& ObjName, const wstring& localPathTexture)
{
	GameObject* Obj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(tag);
	
	Obj->name = ObjName;

	Vec3 test = transform->position + transform->forward * 2;
	Obj->transform->position = test;

	Pickable* pick = Obj->AddComponent<Pickable>();
	
	pick->PushInVector(Type::Map);
	pick->Settings(UVScale, comboBox, localPathTexture, ColliderExistence);

	Obj->transform->scale = Size;
	Obj->transform->SetEulerAngle(Rotation);

	return pick;
}

Pickable* FreePerspectiveCamera::Add_TriggerObject(int cnt)
{
	GameObject* Obj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(L"trigger");

	CString name = L"Trigger_";
	CString num;
	num.Format(_T("%d"), cnt);
	name += num;
	
	Obj->name = name.GetString();

	Vec3 test = transform->position + transform->forward * 2;
	Obj->transform->position = test;

	Pickable* pick = Obj->AddComponent<Pickable>();

	pick->PushInVector(Type::Trigger);

	pick->Settings(Vec2(1.f, 1.f), COMBOBOX::Cube, BuiltInTransparentGreenTexture, true);

	Obj->transform->scale = Vec3(1.f, 1.f, 1.f);
	Obj->transform->SetEulerAngle(Vec3(0.f, 0.f, 0.f));

	return pick;
}

Pickable* FreePerspectiveCamera::Add_EventObject(Pickable* Trigger, int cnt)
{
	GameObject* Obj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(L"Event");

	CString name = L"Event_";
	CString num;
	num.Format(_T("%d"), cnt);
	name += num;
	Obj->name = name.GetString();

	Vec3 test = transform->position + transform->forward * 2;
	Obj->transform->position = test;

	Pickable* Event = Obj->AddComponent<Pickable>();
	Trigger->PushInEventVector(Event);

	Event->Settings(Vec2(1.f, 1.f), COMBOBOX::Cube, L"../SharedResource/Texture/object/Event.png", true);

	Obj->transform->scale = Vec3(1.f, 1.f, 1.f);
	Obj->transform->SetEulerAngle(Vec3(0.f, 0.f, 0.f));

	return Event;
}

HandlingObject* FreePerspectiveCamera::Add_HandlingObject(int cnt)
{
	GameObject* Obj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(L"HandlingObject");

	CString name = L"Object_";
	CString num;
	num.Format(_T("%d"), cnt);
	name += num;
	Obj->name = name.GetString();

	Vec3 Position = transform->position + transform->forward * 2;
	Obj->transform->position = Position;

	HandlingObject* Handling = Obj->AddComponent<HandlingObject>();

	Obj->transform->scale = Vec3(1.f, 1.f, 1.f);
	Obj->transform->SetEulerAngle(Vec3(0.f, 0.f, 0.f));

	return Handling;
}

