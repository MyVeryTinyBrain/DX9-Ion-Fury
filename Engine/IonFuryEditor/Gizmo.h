#pragma once

class Gizmo : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	// ���� �����Ϸ��� �õ��մϴ�.
	// ���� ���õǸ� True�� ��ȯ�մϴ�.
	bool PickHandle();

	// ���� ������ ����մϴ�.
	void PutHandle();

	// ���� ���õǾ������� ��ȯ�մϴ�.
	bool HasSelect() const;

	// X���� ���õǾ������� ��ȯ�մϴ�.
	bool HasAxisX() const;

	// Y���� ���õǾ������� ��ȯ�մϴ�.
	bool HasAxisY() const;

	// Z���� ���õǾ������� ��ȯ�մϴ�.
	bool HasAxisZ() const;

	// ������Ʈ�� ����� ���Դϴ�.
	void Attach(Transform* root);

	// ������Ʈ���� ����� ���ϴ�.
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

