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

	GameObject* m_leftHandObj = nullptr;

	UserMeshRenderer* m_rightHandRenderer = nullptr;

	UserMeshRenderer* m_leftHandRenderer = nullptr;

	int m_totalAmmo = 100;

	int m_loadedAmmo = 10;

	int m_ammoLoadMax = 10;
};

