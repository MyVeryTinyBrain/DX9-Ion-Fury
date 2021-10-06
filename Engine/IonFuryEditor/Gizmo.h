#pragma once

class Gizmo : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	// 축을 선택하려고 시도합니다.
	// 축이 선택되면 True를 반환합니다.
	bool PickHandle();

	// 축의 선택을 취소합니다.
	void PutHandle();

	// 축이 선택되었는지를 반환합니다.
	bool HasSelect() const;

	// X축이 선택되었는지를 반환합니다.
	bool HasAxisX() const;

	// Y축이 선택되었는지를 반환합니다.
	bool HasAxisY() const;

	// Z축이 선택되었는지를 반환합니다.
	bool HasAxisZ() const;

	// 오브젝트에 기즈모를 붙입니다.
	void Attach(Transform* root);

	// 오브젝트에서 기즈모를 뗍니다.
	void Detach();

	Transform* GetSelectedObject() const;

public:
	void DeleteAttachedObject();
	void ChangeTextureAttachedObject(CString texturePath);

private:

	void ResetGizmoTransform();

	void Handling();

	Vec3 CalcGizmoHandlingCoord();

private:

	enum GIZMO_AXIS { GIZMO_AXIS_X, GIZMO_AXIS_Y, GIZMO_AXIS_Z, GIZMO_AXIS_NONE };

	GameObject* m_gizmoParentObj;

	GameObject* m_axisObj[3];

	UserMeshRenderer* m_renderer[3];

	GIZMO_AXIS m_select = GIZMO_AXIS_NONE;

	Vec3 m_selectedPosition = Vec3::zero();

	Vec3 m_selectCoord = Vec3::zero();

	Ref<Transform> m_selectedTransform;

};

