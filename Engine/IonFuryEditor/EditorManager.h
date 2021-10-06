#pragma once

class EditorManager : public Component
{
	// ���� ������Ʈ�� ����κ��Դϴ�.
	DeclareStaticComponent(EditorManager);

	OverrideComponentFunction(Awake);

public:

	class FreePerspectiveCamera* GetPerspectiveCamera();

	class Gizmo* GetGizmo();



private:

	class FreePerspectiveCamera* m_perspectiveCamera;

	class Gizmo* m_gizmo;

};

