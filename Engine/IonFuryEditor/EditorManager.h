#pragma once

class EditorManager : public Component
{
	// 싱글톤 선언부분입니다.
	DeclareSingletone(EditorManager);

	OverrideComponentFunction(Awake);

public:

	class FreePerspectiveCamera* GetPerspectiveCamera();

	class Gizmo* GetGizmo();



private:

	class FreePerspectiveCamera* m_perspectiveCamera;

	class Gizmo* m_gizmo;
};

