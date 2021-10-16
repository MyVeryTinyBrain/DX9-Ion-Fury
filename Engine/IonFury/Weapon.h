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

	// 이 무기로 변경되었을 떄 호출됩니다.
	virtual void OnChanged() = 0;

	// 이 무기를 집어 넣을 때 호출됩니다.
	virtual void OnPutIn() = 0;

	// 공격 키 상태가 전송됩니다.
	virtual void OnAttackInput(InputType inputType) = 0;

	// 보조 키 상태가 전송됩니다.
	virtual void OnSubInput(InputType inputType) = 0;

	// 재장전 키 상태가 전송됩니다.
	virtual void OnReloadInput(InputType inputType) = 0;
};

