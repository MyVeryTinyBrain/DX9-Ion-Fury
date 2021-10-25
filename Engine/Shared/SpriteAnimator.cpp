#include "shared_stdafx.h"
#include "SpriteAnimator.h"
#include "SpriteAnimation.h"

void SpriteAnimator::Awake()
{
	if (!m_renderer)
	{
		auto renderer = gameObject->GetComponent<UserMeshRenderer>();
		SetRenderer(renderer);
	}

	if (m_renderer && m_default != nullptr)
	{
		Texture* firstTexture = nullptr;
		m_default->IndexOf(0, &firstTexture);
		m_renderer->SetTexture(0, firstTexture);
	}
}

void SpriteAnimator::Start()
{
	if (!m_renderer)
	{
		auto renderer = gameObject->GetComponent<UserMeshRenderer>();
		SetRenderer(renderer);
	}

	if (m_renderer && m_default != nullptr)
	{
		Texture* firstTexture = nullptr;
		m_default->IndexOf(0, &firstTexture);
		m_renderer->SetTexture(0, firstTexture);
	}
}

void SpriteAnimator::AnimationUpdate()
{
	// 경과된 시간에 알맞는 텍스쳐를 렌더러에 올립니다.
	UpdateTexture();

	// 애니메이션이 변경되어야 하면 변경합니다.
	Transition();
}

const Ref<UserMeshRenderer>& SpriteAnimator::GetRenderer() const
{
	return m_renderer;
}

void SpriteAnimator::SetRenderer(const Ref<UserMeshRenderer>& renderer)
{
	m_renderer = renderer;
}

void SpriteAnimator::PlayAnimation(SpriteAnimation* animation, bool overlap, bool keepElapsed)
{
	Resume();

	// 이미 재생중인 애니메이션을 재생하려고 할때 overlap 플래그가 꺼져있다면 종료합니다.
	if (!overlap && animation == m_current)
	{
		return;
	}

	// 애니메이션 변경 이벤트함수를 호출합니다.
	OnAnimationChange(m_current, &animation);

	if (!keepElapsed)
	{
		m_elapsed = 0;
	}
	m_current = animation;

	// 텍스쳐를 업데이트합니다.
	UpdateTexture();
}

void SpriteAnimator::SetDefaultAnimation(SpriteAnimation* animation, bool play)
{
	if (m_default == animation)
	{
		return;
	}

	// 기본 애니메이션 변경 이벤트함수를 호출합니다.
	OnDefaultAnimationChange(m_default, &animation);

	m_default = animation;

	if (play)
	{
		PlayAnimation(animation, false);
	}
}

void SpriteAnimator::PlayDefaultAnimation(bool overlap)
{
	PlayAnimation(m_default, overlap);
}

SpriteAnimation* SpriteAnimator::GetCurrentAnimation() const
{
	return m_current;
}

SpriteAnimation* SpriteAnimator::GetDefaultAnimation() const
{
	return m_default;
}

bool SpriteAnimator::GetTransitionMode() const
{
	return m_transition;
}

void SpriteAnimator::SetTransitionMode(bool value)
{
	m_transition = value;
}

void SpriteAnimator::Pause()
{
	m_pause = true;
}

void SpriteAnimator::Resume()
{
	m_pause = false;
}

float SpriteAnimator::GetSpeed() const
{
	return m_speed;
}

void SpriteAnimator::SetSpeed(float value)
{
	m_speed = value;
}

float SpriteAnimator::GetElapsedTime() const
{
	return m_elapsed;
}

void SpriteAnimator::SetElapsedTime(float value)
{
	m_elapsed = value;
}

float SpriteAnimator::GetPercent() const
{
	if (!m_current)
	{
		return 0.0f;
	}

	return m_elapsed / m_current->maxTime;
}

unsigned int SpriteAnimator::GetFrameIndex() const
{
	return unsigned int(GetPercent() * m_current->textureCount);
}

void SpriteAnimator::UpdateTexture()
{
	if (!m_renderer) return;
	if (!m_current) return;

	Texture* texture = nullptr;
	bool endOfAnimation = !m_current->TimeOf(m_elapsed, &texture);
	
	if (texture)
	{
		m_renderer->SetTexture(0, texture);
	}
}

void SpriteAnimator::Transition()
{
	if (!m_renderer) return;
	if (!m_current) return;

	// 경과 시간에 누적합니다.
	if (!m_pause)
		m_elapsed += Time::DeltaTime() * m_speed;

	// 루프 애니메이션이 아닌데, 애니메이션의 끝인 경우
	if (!m_current->isLoop && m_current->IsEnd(m_elapsed))
	{
		SpriteAnimation* current = m_current;

		// 애니메이션 종료 이벤트함수를 호출합니다.
		OnAnimationEnd(current);

		// OnAnimationEnd 내부에서 애니메이션이 변경되지 않았다면 현재 애니메이션을 nullptr로 합니다.
		if (m_current == current)
		{
			m_current = nullptr;
		}

		// OnAnimationEnd() 에서 다른 애니메이션이 설정되지 않은 경우에
		if (m_current == nullptr)
		{
			// 애니메이션을 변경하지 않는 조건이면 종료합니다.
			if (!m_transition)
			{
				return;
			}

			m_current = current;

			// 기본 애니메이션으로 전환합니다.
			PlayAnimation(m_default, true);

			// 변경된 애니메이션의 텍스쳐를 적용합니다.
			UpdateTexture();
		}
	}
}
