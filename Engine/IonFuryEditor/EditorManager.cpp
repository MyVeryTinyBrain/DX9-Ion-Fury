#include "IonFuryEditorBase.h"
#include "EditorManager.h"

// ���⿡ �Ե��� ���� ��� �߰��ϼ�.
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"

// �̱����� ���Ǻκ��Դϴ�.
ImplementSingletone(EditorManager);

void EditorManager::Awake()
{
	// ���⿡�� �Ե��� ���� ������Ʈ������ �߰��ϼ�.
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
