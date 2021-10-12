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

	// �� Ŭ������ ��ӹ��� �ʰ� �ٷ� ����� �� �ֽ��ϴ�.
	// �� �Լ��� ȣ���ϸ� �ִϸ��̼��� ���� �� �ִϸ��̼��� ���� �����մϴ�.
	void AddTexture(const wstring& textureLocalPath);

protected:

	// �� Ŭ������ ��ӹ޾Ƽ� ������ ����Ʈ�� ����ϴµ� ����� �� �ֽ��ϴ�.
	virtual void InitializeAnimation(SpriteAnimation** ppAnimation) {};

private:

	SpriteAnimation* m_animation = nullptr;

	UserMeshRenderer* m_renderer = nullptr;

	bool m_requireDestroy = false;
};

