#include "IonFuryEditorBase.h"
#include "LightManager.h"
#include "EditorManager.h"
#include "Gizmo.h"
#include "../Engine/header/SpotLight.h"
#include "../Engine/header/PointLight.h"
#include "../Engine/header/Light.h"
#include "FreePerspectiveCamera.h"

// 정석 컴포넌트의 정의부분입니다.
ImplementStaticComponent(LightManager);

std::vector<LightObject*> LightManager::g_LightVec;

void LightManager::Awake()
{
	// 정적 변수에 대입합니다.
	g_instance = this;

//g_LightVec.push_back(this);


	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
}

void LightManager::Update()
{
	if (Input::GetKeyDown(Key::LeftMouse))
		LightPick();
}

void LightManager::OnDestroy()
{
	auto it = FindInContainer(g_LightVec, this);
	if (it != g_LightVec.end())
		g_LightVec.erase(it);
}


LightManager* LightManager::LightPick()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;


	for (auto pickable : g_LightVec)
	{
		UserMeshRenderer* Renderer = pickable

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			EditorManager::GetInstance()->GetGizmo()->Attach(Get);
			return pickable;
		}
	}

	return nullptr;
}

void LightManager::AddLight(const tag_t& tag, const wstring& LightName, const wstring& localPathMesh)
{
	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();

	if (tag == L"Point")
	{
		GameObject* PointLightObj = CreateGameObject(tag);

		PointLightObj->name = LightName;


		//이게 맞을까낭... 음!!
		PointLightObj->transform->position = transform->position + transform->forward * 2;

		auto LightObj = PointLightObj->AddComponent<PointLight>();
	}
	else if (tag == L"Spot")
	{
		GameObject* SpotLightObj = CreateGameObject(tag);

		SpotLightObj->name = LightName;

		SpotLightObj->transform->parent = camera->transform;

		auto LightObj = SpotLightObj->AddComponent<SpotLight>();
	}
}

