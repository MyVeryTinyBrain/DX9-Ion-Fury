#include "IonFuryEditorBase.h"
#include "EditorManager.h"

// ���⿡ �Ե��� ���� ��� �߰��ϼ�.
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"

// ���� ������Ʈ�� ���Ǻκ��Դϴ�.
ImplementStaticComponent(EditorManager);

void EditorManager::Awake()
{
	// ���� ������ �����մϴ�.
	g_instance = this;

	// ���⿡�� �Ե��� ���� ������Ʈ������ �߰��ϼ�.
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

	{	// �𷺼ų� ����Ʈ ����
		auto directionalLightObj = CreateGameObject();
		auto dl = directionalLightObj->AddComponent<DirectionalLight>();
		dl->color = Color::white() * 0.8f;
		dl->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
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
