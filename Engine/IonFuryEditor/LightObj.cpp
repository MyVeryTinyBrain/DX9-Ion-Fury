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
	}
	else if (obj->tag == L"Spot")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<SpotLight>();
	}
	else if (obj->tag == L"DirectionalLight")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<DirectionalLight>();
	}

	g_vecLight.push_back(this);

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
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
