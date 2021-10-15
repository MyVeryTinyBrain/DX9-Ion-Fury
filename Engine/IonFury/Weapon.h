#pragma once

class FPSOrthoCamera;

class Weapon abstract : public Component
{
public:

	enum class InputType
	{
		KeyDown, KeyPressing, KeyUp, Nothing
	};

public:

	// �� ����� ����Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnChanged() = 0;

	// �� ���⸦ ���� ���� �� ȣ��˴ϴ�.
	virtual void OnPutIn() = 0;

	// ���� Ű ���°� ���۵˴ϴ�.
	virtual void OnAttackInput(InputType inputType) = 0;

	// ���� Ű ���°� ���۵˴ϴ�.
	virtual void OnSubInput(InputType inputType) = 0;

	// ������ Ű ���°� ���۵˴ϴ�.
	virtual void OnReloadInput(InputType inputType) = 0;
};

