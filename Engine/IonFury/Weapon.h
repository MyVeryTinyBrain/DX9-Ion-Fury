#pragma once

class FPSOrthoCamera;

class Weapon abstract : public Component
{
public:

	enum class InputType
	{
		KeyDown, KeyPressing, KeyUp, Nothing
	};

private:

	OverrideComponentFunction(Awake);

public:

	// �� ����� ����Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnChanged() = 0;

	// ���� Ű ���°� ���۵˴ϴ�.
	virtual void OnAttackInput(InputType inputType) = 0;

	// ���� Ű ���°� ���۵˴ϴ�.
	virtual void OnSubInput(InputType inputType) = 0;

	// ������ Ű ���°� ���۵˴ϴ�.
	virtual void OnReloadInput(InputType inputType) = 0;

protected:

	GameObject* m_rightHandObj = nullptr;

	UserMeshRenderer* m_rightHandRenderer = nullptr;
};

