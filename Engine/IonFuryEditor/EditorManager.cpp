#include "IonFuryEditorBase.h"
#include "EditorManager.h"

// 여기에 님들이 만든 헤더 추가하셈.
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"
#include "LightObj.h"

// 정석 컴포넌트의 정의부분입니다.
ImplementStaticComponent(EditorManager);

void EditorManager::Awake()
{
	// 정적 변수에 대입합니다.
	g_instance = this;

	// 여기에서 님들이 만든 컴포넌트같은거 추가하셈.
	{
		GameObject* cameraObj = CreateGameObject(L"FreePerspectiveCamera");
		cameraObj->transform->position = Vec3(0, 0, -5);
		cameraObj->AddComponent<Camera>();
		m_perspectiveCamera = cameraObj->AddComponent<FreePerspectiveCamera>();
	}

	{
		GameObject* gizmoObj = CreateGameObject(L"Gizmo");
		m_gizmo = gizmoObj->AddComponent<Gizmo>();
	}

	{	
		// 자연광을 설정합니다.
		Light::SetGlobalAmbientLight(Color::white() * 0.7f);

		// 디렉셔널 라이트 생성
		auto directionalLightObj = CreateGameObject(L"Directional");
		directionalLightObj->name = L"Directional";
		auto dl = directionalLightObj->AddComponent<LightObj>();

		/// <summary>
		/// ////////////여기서부터 하면돼
		/// </summary>
		auto dll = dl->GetGameObject()->GetComponent<DirectionalLight>();
		dl->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
		dll->color = Color::white() * 0.8f;
	}
	///////////////////////////////////////
}

FreePerspectiveCamera* EditorManager::GetPerspectiveCamera()
{
	return m_perspectiveCamera;
}

Gizmo* EditorManager::GetGizmo()
{
	return m_gizmo;
}

