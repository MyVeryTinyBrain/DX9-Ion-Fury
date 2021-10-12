#pragma once

// �� ������Ʈ�� �����ǰ� ���� ������ ���۵� �� �ڵ����� ���� ���ӿ�����Ʈ�� �������� ã���ϴ�.
// �Ǵ� SetRenderer() �� ȣ���Ͽ� ���� �������� �����Ҽ� �ֽ��ϴ�.

class SpriteAnimation;

class SpriteAnimator abstract : public Component
{
	OverrideComponentFunction(Start);

	OverrideComponentFunction(AnimationUpdate);

protected:

	// ���� �÷��װ� ���� �ִϸ��̼��� ����� �� ȣ��˴ϴ�.
	virtual void OnAnimationEnd(const SpriteAnimation* current) = 0;

	// �ִϸ��̼��� ����� �� ȣ��˴ϴ�.
	// next�� �ٸ� �ִϸ��̼��� �����Ͽ� ����� �ִϸ��̼��� �缳�����ټ��� �ֽ��ϴ�.
	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) = 0;

	// �⺻ �ִϸ��̼��� ����� �� ȣ��˴ϴ�.
	// next�� �ٸ� �ִϸ��̼��� �����Ͽ� ����� �⺻ �ִϸ��̼��� �缳�����ټ��� �ֽ��ϴ�.
	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) = 0;

public:

	const Ref<UserMeshRenderer>& GetRenderer() const;

	void SetRenderer(const Ref<UserMeshRenderer>& renderer);

	void PlayAnimation(SpriteAnimation* animation, bool overlap = false, bool keepElapsed = false);

	void SetDefaultAnimation(SpriteAnimation* animation, bool play = true);

	void PlayDefaultAnimation(bool overlap = true);

	SpriteAnimation* GetCurrentAnimation() const;

	SpriteAnimation* GetDefaultAnimation() const;

	bool GetTransitionMode() const;

	void SetTransitionMode(bool value);

	void Pause();

	void Resume();

	float GetSpeed() const;

	void SetSpeed(float value);

	float GetElapsedTime() const;

	void SetElapsedTime(float value);

	float GetPercent() const;

	unsigned int GetFrameIndex() const;

	__declspec(property(get = GetCurrentAnimation)) SpriteAnimation* currentAnimation;

	__declspec(property(get = GetDefaultAnimation)) SpriteAnimation* defaultAnimation;

private:

	void UpdateTexture();

	void Transition();

private:

	Ref<UserMeshRenderer> m_renderer;

	float m_elapsed = 0;

	SpriteAnimation* m_current = nullptr;

	SpriteAnimation* m_default = nullptr;

	float m_speed = 1.0f;

	bool m_pause = false;

	bool m_transition = true;
};

