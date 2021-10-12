#pragma once

// 이 컴포넌트가 부착되고 다음 프레임 시작될 때 자동으로 같은 게임오브젝트의 렌더러를 찾습니다.
// 또는 SetRenderer() 를 호출하여 직접 렌더러를 설정할수 있습니다.

class SpriteAnimation;

class SpriteAnimator abstract : public Component
{
	OverrideComponentFunction(Start);

	OverrideComponentFunction(AnimationUpdate);

protected:

	// 루프 플래그가 없는 애니메이션이 종료될 때 호출됩니다.
	virtual void OnAnimationEnd(const SpriteAnimation* current) = 0;

	// 애니메이션이 변경될 때 호출됩니다.
	// next에 다른 애니메이션을 전달하여 변경될 애니메이션을 재설정해줄수도 있습니다.
	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) = 0;

	// 기본 애니메이션이 변경될 때 호출됩니다.
	// next에 다른 애니메이션을 전달하여 변경될 기본 애니메이션을 재설정해줄수도 있습니다.
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

