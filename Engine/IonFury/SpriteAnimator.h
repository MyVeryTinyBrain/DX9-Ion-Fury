#pragma once

// 이 컴포넌트가 부착되고 다음 프레임 시작될 때 자동으로 같은 게임오브젝트의 렌더러를 찾습니다.
// 또는 SetRenderer() 를 호출하여 직접 렌더러를 설정할수 있습니다.

class SpriteAnimation;

class SpriteAnimator abstract : public Component
{
	OverrideComponentFunction(Start);

	OverrideComponentFunction(AnimationUpdate);

	OverrideComponentFunction(Update);

protected:

	// 루프 플래그가 없는 애니메이션이 종료될 때 호출됩니다.
	virtual void OnAnimationEnd() = 0;

	// 애니메이션이 변경될 때 호출됩니다.
	// next에 다른 애니메이션을 전달하여 변경될 애니메이션을 재설정해줄수도 있습니다.
	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) = 0;

	// 기본 애니메이션이 변경될 때 호출됩니다.
	// next에 다른 애니메이션을 전달하여 변경될 기본 애니메이션을 재설정해줄수도 있습니다.
	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) = 0;

public:

	const Ref<Renderer>& GetRenderer() const;

	void SetRenderer(const Ref<Renderer>& renderer);

	void PlayAnimation(SpriteAnimation* animation, bool overlap = false);

	void SetDefaultAnimation(SpriteAnimation* animation, bool play = true);

	void PlayDefaultAnimation(bool overlap = true);

	SpriteAnimation* GetCurrentAnimation() const;

	SpriteAnimation* GetDefautlAnimation() const;

	bool GetTransitionMode() const;

	void SetTransitionMode(bool value);

	void Pause();

	void Resume();

	float GetSpeed() const;

	void SetSpeed(float value);

	float GetElapsedTime() const;

	float GetPercent() const;

	unsigned int GetFrameIndex() const;

private:

	void UpdateTexture();

private:

	Ref<Renderer> m_renderer;

	float m_elapsed = 0;

	SpriteAnimation* m_current = nullptr;

	SpriteAnimation* m_default = nullptr;

	float m_speed = 1.0f;

	bool m_pause = false;

	bool m_transition = true;
};

