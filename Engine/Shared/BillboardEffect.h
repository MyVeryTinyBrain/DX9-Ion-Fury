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

	// �� Ŭ������ ��ӹ��� �ʰ� �ٷ� ����� �� �ֽ��ϴ�.
	// �� �Լ��� ȣ���ϸ� �ִϸ��̼��� ���� �� �ִϸ��̼��� ���� �����մϴ�.
	void AddTexture(const wstring& textureLocalPath);

	// �ִϸ��̼��� �� �ð����� ����ǵ��� ������ ������ ����ϴ�.
	// �ִϸ��̼��� ��� ������ ���Ŀ� ȣ���ϵ��� �մϴ�.
	void FitIntervalToTime(float time);

	void SetToAlphaTest();

	void SetToTransparent();

	void SetInterval(float value);

	bool IsIgnoreZRotation() const;

	void SetIgnoreZRotation(bool value);

	UserMeshBillboardRenderer* GetBillboardRenderer() const;

protected:

	// �� Ŭ������ ��ӹ޾Ƽ� ������ ����Ʈ�� ����ϴµ� ����� �� �ֽ��ϴ�.
	virtual void InitializeAnimation(SpriteAnimation** ppAnimation) {};

private:

	SpriteAnimation* m_animation = nullptr;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	bool m_requireDestroy = false;
};

