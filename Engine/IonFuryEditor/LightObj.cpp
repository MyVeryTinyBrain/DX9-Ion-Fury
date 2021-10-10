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
	auto obj = this->GetGameObject();
	
	if (obj->tag == L"PointLight")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<PointLight>();
	}
	else if (obj->tag == L"SpotLight")
	{
		m_LightChildObject = CreateGameObjectToChild(transform);
		m_LightChildObject->AddComponent<SpotLight>();
	}

	g_vecLight.push_back(this);
}


void LightObj::Update()
{
	if (m_destroyRequire)
	{
		gameObject->Destroy();
		return;
	}

	if (Input::GetKeyDown(Key::LeftMouse))
		LightPick();
}

void LightObj::OnDestroy()
{
	auto it = FindInContainer(g_vecLight, this);
	if (it != g_vecLight.end())
		g_vecLight.erase(it);
}

void LightObj::LightSettings(const wstring& localPathMesh, const wstring& localPathTexture)
{
	m_LightRenderer = m_LightChildObject->AddComponent<UserMeshRenderer>();
	m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
	m_LightRenderer->SetTexture(0, Resource::FindAs<Texture>(localPathTexture));
}


LightObj* LightObj::LightPick()
{
	/*Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;
	for (auto pickable : g_vecLight)
	{
		UserMeshRenderer* Renderer = pickable->GetRenderer();

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			EditorManager::GetInstance()->GetGizmo()->Attach(pickable->transform);
			return pickable;
		}
	}*/

	return nullptr;
}

void LightObj::RequireDestroy()
{
	m_destroyRequire = true;
}
