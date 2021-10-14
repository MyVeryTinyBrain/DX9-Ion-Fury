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
	auto meshRendererObj = CreateGameObjectToChild(gameObject->transform);

	m_LightRenderer = meshRendererObj->AddComponent<UserMeshRenderer>();
	m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCyilinderUserMesh);
	m_LightRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
	meshRendererObj->transform->localEulerAngle = Vec3(90, 0, 0);
}

LightObj* LightObj::LightPick()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	for (auto pickable : g_vecLight)
	{
		auto obj = pickable->GetGameObject();
		auto Renderer = obj->GetComponent<UserMeshRenderer>();
		//UserMeshRenderer* Renderer = 

		if (Renderer)
		{
			if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
			{
				giz->enable = true;
				EditorManager::GetInstance()->GetGizmo()->Attach(pickable->GetGameObject()->transform);
				return pickable;
			}
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
