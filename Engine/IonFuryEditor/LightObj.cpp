#include "IonFuryEditorBase.h"
#include "LightObj.h"
#include "EditorManager.h"
#include "Gizmo.h"
#include "../Engine/header/SpotLight.h"
#include "../Engine/header/PointLight.h"
#include "FreePerspectiveCamera.h"

// 정석 컴포넌트의 정의부분입니다.
ImplementStaticComponent(LightObj);

std::vector<LightObj*> LightObj::g_LightVec;

void LightObj::Awake()
{
	// 정적 변수에 대입합니다.
	g_instance = this;

	m_LightChildObject = CreateGameObject();

	m_LightChildObject->transform->parent = GetGameObject()->transform;
	m_LightChildObject->transform->localPosition = Vec3::zero();

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
}

void LightObj::Update()
{
	if (Input::GetKeyDown(Key::LeftMouse))
		LightPick();
}

void LightObj::OnDestroy()
{
	auto it = FindInContainer(g_LightVec, this);
	if (it != g_LightVec.end())
		g_LightVec.erase(it);
}

void LightObj::LightSettings(const wstring& localPathMesh)
{
	m_LightRenderer = m_LightChildObject->AddComponent<UserMeshRenderer>();
	m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
}

LightObj* LightObj::LightPick()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;

	for (auto pickable : g_LightVec)
	{
		UserMeshRenderer* Renderer = pickable->GetRenderer();

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			EditorManager::GetInstance()->GetGizmo()->Attach(pickable->transform);
			return pickable;
		}
	}

	return nullptr;
}
//
//void LightObj::AddLight(const tag_t& tag, const wstring& LightName, const wstring& localPathMesh)
//{
//	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();
//
//	if (tag == L"Point")
//	{
//		GameObject* PointLightObj = CreateGameObject(tag);
//
//		PointLightObj->name = LightName;
//
//
//		//이게 맞을까낭... 음!!
//		PointLightObj->transform->position = transform->position + transform->forward * 2;
//
//		auto LightObj = PointLightObj->AddComponent<PointLight>();
//	}
//	else if (tag == L"Spot")
//	{
//		GameObject* SpotLightObj = CreateGameObject(tag);
//
//		SpotLightObj->name = LightName;
//
//		SpotLightObj->transform->parent = camera->transform;
//
//		auto LightObj = SpotLightObj->AddComponent<SpotLight>();
//	}
//}
//
