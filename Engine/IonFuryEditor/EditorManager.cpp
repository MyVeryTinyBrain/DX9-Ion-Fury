#include "IonFuryEditorBase.h"
#include "EditorManager.h"

// ���⿡ �Ե��� ���� ��� �߰��ϼ�.
#include "FreePerspectiveCamera.h"
#include "Gizmo.h"
#include "LightObj.h"

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

	{	
		// �ڿ����� �����մϴ�.
		Light::SetGlobalAmbientLight(Color::white() * 0.7f);

		// �𷺼ų� ����Ʈ ����
		auto directionalLightObj = CreateGameObject(L"Directional");
		directionalLightObj->name = L"Directional";
		auto dl = directionalLightObj->AddComponent<LightObj>();

		/// <summary>
		/// ////////////���⼭���� �ϸ��
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

