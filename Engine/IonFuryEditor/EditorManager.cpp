#include "IonFuryEditorBase.h"
#include "EditorManager.h"

// 여기에 님들이 만든 헤더 추가하셈.
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"

// 싱글톤의 정의부분입니다.
ImplementSingletone(EditorManager);

void EditorManager::Awake()
{
	// 여기에서 님들이 만든 컴포넌트같은거 추가하셈.
	{
		GameObject* cameraObj = CreateGameObject(L"FreePerspectiveCamera");
		cameraObj->transform->position = Vec3(0, 0, -5);
		cameraObj->AddComponent<Camera>();
		m_perspectiveCamera = cameraObj->AddComponent<FreePerspectiveCamera>();
	}

	{
		GameObject* gizmoObj = CreateGameObject(L"Gizmo");
		gizmoObj->AddComponent<Gizmo>();
	}

	
}

FreePerspectiveCamera* EditorManager::GetPerspectiveCamera()
{
	return m_perspectiveCamera;
}

Gizmo* EditorManager::GetGizmo()
{
	return m_gizmo;
}
