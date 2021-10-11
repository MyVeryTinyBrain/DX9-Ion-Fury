#include "IonFuryEditorBase.h"
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"
#include "Pickable.h"
#include "EditorManager.h"
#include "LightObj.h"


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

	if (Input::GetKeyDown(Key::M))
		EditorManager::GetInstance()->GetGizmo()->DeleteAttachedObject();

	if (Input::GetKeyDown(Key::L))
		EditorManager::GetInstance()->GetGizmo()->GetInformation();


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

void FreePerspectiveCamera::Add_Object_Sample(const tag_t& tag, const wstring& ObjName, const wstring& localPathMesh, const wstring& localPathTexture)
{
	if (localPathMesh.length() < 1)
		return;
	GameObject* Obj = CreateGameObject(tag);

	Obj->name = ObjName;

	Obj->transform->position = transform->position + transform->forward * 2;
	

	auto test = Obj->AddComponent<Pickable>();
	test->Settings(localPathMesh, localPathTexture);
}

void FreePerspectiveCamera::AddLight(const wstring& LightName ,	const wstring& LightType)
{
	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();

	if (LightType == L"Point")
	{
		GameObject* PointLightObj = CreateGameObject(L"PointLight");


		PointLightObj->name = LightName;

		PointLightObj->transform->position = transform->position + transform->forward * 2;

		auto point = PointLightObj->AddComponent<LightObj>();
		//point->LightSettings(localPathMesh, localPathTexture);
	}
	else if (LightType == L"Spot")
	{
		GameObject* SpotLightObj = CreateGameObject(L"SpotLight");

		SpotLightObj->name = LightName;

		SpotLightObj->transform->position = transform->position + transform->forward * 2;

		auto spot = SpotLightObj->AddComponent<LightObj>();
		//spot->LightSettings(localPathMesh, localPathTexture);
	}
}
