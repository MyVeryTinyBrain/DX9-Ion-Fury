#pragma once

class EditorManager : public Component
{
	// �̱��� ����κ��Դϴ�.
	DeclareSingletone(EditorManager);

	OverrideComponentFunction(Awake);

public:

	class FreePerspectiveCamera* GetPerspectiveCamera();

	class Gizmo* GetGizmo();



private:

	class FreePerspectiveCamera* m_perspectiveCamera;

	class Gizmo* m_gizmo;
};

