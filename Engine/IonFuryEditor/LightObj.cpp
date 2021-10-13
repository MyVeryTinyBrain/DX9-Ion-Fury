#include "IonFuryEditorBase.h"
#include "LightObj.h"
#include "EditorManager.h"
#include "Gizmo.h"
#include "../Engine/header/SpotLight.h"
#include "../Engine/header/PointLight.h"
#include "FreePerspectiveCamera.h"

std::vector<LightObj*> LightObj::g_vecLight;

void LightObj::Awake()
{
	//Light::Awake();

	auto obj = this->GetGameObject();

	if (obj->tag == L"Point")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<PointLight>();
		EditorManager::GetInstance()->GetGizmo()->Attach(transform);
	}
	else if (obj->tag == L"Spot")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<SpotLight>();
		EditorManager::GetInstance()->GetGizmo()->Attach(transform);
	}
	else if (obj->tag == L"Directional")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<DirectionalLight>();
		EditorManager::GetInstance()->GetGizmo()->Attach(transform);
	}

	g_vecLight.push_back(this);

}


void LightObj::Update()
{
	//Light::Update();

	if (m_destroyRequire)
	{
		gameObject->Destroy();
		return;
	}

}

void LightObj::OnDestroy()
{
	auto it = FindInContainer(g_vecLight, this);
	if (it != g_vecLight.end())
		g_vecLight.erase(it);
}

void LightObj::LightSetting()
{
	m_LightRenderer = m_LightChildObject->AddComponent<UserMeshRenderer>();
	m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCyilinderUserMesh);
	m_LightRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Light.png"));
}

LightObj* LightObj::LightPick()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;

	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	for (auto light : g_vecLight)
	{
		UserMeshRenderer* Renderer = light->GetRenderer();

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			//transform->position + transform->forward * 2;
			giz->enable = true;
			camera->transform->position = light->transform->position - camera->transform->forward * 2;
		
			return light;
		}
	}

	return nullptr;
}

void LightObj::DeleteMesh()
{
}


void LightObj::LightPick(const CString& name)
{
	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();

	for (auto light : g_vecLight)
	{
		if (light->GetGameObject()->name.c_str() == name)
		{
			EditorManager::GetInstance()->GetGizmo()->Attach(light->GetGameObject()->transform);
			light->GetGameObject()->transform->position = camera->transform->position + camera->transform->forward * 2;
		}
	}

}

void LightObj::RequireDestroy()
{
	m_destroyRequire = true;
}
