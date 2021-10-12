#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class OrthoEffect : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void SetOverlayRenderOrder(int value);

	// 이 클래스를 상속받지 않고 바로 사용할 수 있습니다.
	// 이 함수를 호출하면 애니메이션이 없을 때 애니메이션을 동적 생성합니다.
	void AddTexture(const wstring& textureLocalPath);

protected:

	// 이 클래스를 상속받아서 고정된 이펙트를 출력하는데 사용할 수 있습니다.
	virtual void InitializeAnimation(SpriteAnimation** ppAnimation) {};

private:

	SpriteAnimation* m_animation = nullptr;

	UserMeshRenderer* m_renderer = nullptr;

	bool m_requireDestroy = false;
};

