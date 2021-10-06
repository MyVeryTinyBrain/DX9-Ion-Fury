#pragma once

class EditorManager : public Component
{
	// 정석 컴포넌트의 선언부분입니다.
	DeclareStaticComponent(EditorManager);

	OverrideComponentFunction(Awake);

public:

	class FreePerspectiveCamera* GetPerspectiveCamera();

	class Gizmo* GetGizmo();



private:

	class FreePerspectiveCamera* m_perspectiveCamera;

	class Gizmo* m_gizmo;

};

