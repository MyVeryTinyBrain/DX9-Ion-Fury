#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class BillboardEffect : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	// 이 클래스를 상속받지 않고 바로 사용할 수 있습니다.
	// 이 함수를 호출하면 애니메이션이 없을 때 애니메이션을 동적 생성합니다.
	void AddTexture(const wstring& textureLocalPath);

	// 애니메이션이 이 시간동안 재생되도록 프레임 간격을 맞춥니다.
	// 애니메이션이 모두 설정된 이후에 호출하도록 합니다.
	void FitIntervalToTime(float time);

	void SetToAlphaTest();

	void SetToTransparent();

	void SetInterval(float value);

	bool IsIgnoreZRotation() const;

	void SetIgnoreZRotation(bool value);

	UserMeshBillboardRenderer* GetBillboardRenderer() const;

protected:

	// 이 클래스를 상속받아서 고정된 이펙트를 출력하는데 사용할 수 있습니다.
	virtual void InitializeAnimation(SpriteAnimation** ppAnimation) {};

private:

	SpriteAnimation* m_animation = nullptr;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	bool m_requireDestroy = false;
};

