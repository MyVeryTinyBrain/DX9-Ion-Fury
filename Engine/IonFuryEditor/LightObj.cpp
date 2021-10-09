#include "IonFuryEditorBase.h"
#include "LightObj.h"
#include "EditorManager.h"
#include "Gizmo.h"
#include "../Engine/header/SpotLight.h"
#include "../Engine/header/PointLight.h"
#include "FreePerspectiveCamera.h"

// 정석 컴포넌트의 정의부분입니다.
ImplementStaticComponent(LightObj);

std::vector<LightObj*> LightObj::g_vecLight;

void LightObj::Awake()
{
	// 정적 변수에 대입합니다.
	g_instance = this;

	auto obj = this->GetGameObject();

	m_strType = obj->name.c_str();
	
	if (m_strType == L"Point")
	{
		//m_LightType = LIGHT::POINT;
		m_LightChildObject = CreateGameObject();
		m_LightChildObject->AddComponent<PointLight>();
	}
	else if (m_strType == L"Spot")
	{
		//m_LightType = LIGHT::SPOT;
		m_LightChildObject = CreateGameObject();
		m_LightChildObject->AddComponent<SpotLight>();
	}

	g_vecLight.push_back(this);

	m_LightChildObject->transform->parent = GetGameObject()->transform;
	m_LightChildObject->transform->localPosition = Vec3::zero();
}

void LightObj::Start()
{
	//switch (m_LightType)
	//{
	//case LIGHT::POINT:
	//	m_LightChildObject = CreateGameObject();
	//	m_LightChildObject->AddComponent<PointLight>();
	//	break;
	//case LIGHT::SPOT:
	//	m_LightChildObject = CreateGameObject();
	//	m_LightChildObject->AddComponent<SpotLight>();
	//	break;
	//}

	//g_vecLight.push_back(this);

	//m_LightChildObject->transform->parent = GetGameObject()->transform;
	//m_LightChildObject->transform->localPosition = Vec3::zero();

	//EditorManager::GetInstance()->GetGizmo()->Attach(transform);
}

void LightObj::Update()
{
	if (Input::GetKeyDown(Key::LeftMouse))
		LightPick();
}

void LightObj::OnDestroy()
{
	auto it = FindInContainer(g_vecLight, this);
	if (it != g_vecLight.end())
		g_vecLight.erase(it);
}

void LightObj::LightSettings(const wstring& localPathMesh)
{
	m_LightRenderer = m_LightChildObject->AddComponent<UserMeshRenderer>();
	m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
}

void LightObj::SetLightType(const wstring& lightType)
{
	m_strType = lightType.c_str();
	//if (lightType == L"Point")
	//{
	//	m_LightType = LIGHT::POINT;
	//}
	//else if (lightType == L"Spot")
	//{
	//	m_LightType = LIGHT::SPOT;
	//}
}

LightObj* LightObj::LightPick()
{
	//Vec3 rayPoint, rayDir;
	//Input::GetMouseWorldRay(rayPoint, rayDir);

	//Vec3 HitPoint;
	//for (auto pickable : g_vecLight)
	//{
	//	UserMeshRenderer* Renderer = pickable->GetRenderer();

	//	if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
	//	{
	//		EditorManager::GetInstance()->GetGizmo()->Attach(pickable->transform);
	//		return pickable;
	//	}
	//}

	return nullptr;
}
