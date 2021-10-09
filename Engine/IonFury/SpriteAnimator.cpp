#include "stdafx.h"
#include "SpriteAnimator.h"
#include "SpriteAnimation.h"

void SpriteAnimator::Start()
{
	if (!m_renderer)
	{
		auto renderer = gameObject->GetComponent<Renderer>();
		SetRenderer(renderer);
	}
}

void SpriteAnimator::AnimationUpdate()
{
	// ����� �ð��� �˸´� �ؽ��ĸ� �������� �ø��ϴ�.
	UpdateTexture();

	// �ִϸ��̼��� ����Ǿ�� �ϸ� �����մϴ�.
	Transition();
}

const Ref<Renderer>& SpriteAnimator::GetRenderer() const
{
	return m_renderer;
}

void SpriteAnimator::SetRenderer(const Ref<Renderer>& renderer)
{
	m_renderer = renderer;
}

void SpriteAnimator::PlayAnimation(SpriteAnimation* animation, bool overlap)
{
	Resume();

	// �̹� ������� �ִϸ��̼��� ����Ϸ��� �Ҷ� overlap �÷��װ� �����ִٸ� �����մϴ�.
	if (!overlap && animation == m_current)
	{
		return;
	}

	// �ִϸ��̼� ���� �̺�Ʈ�Լ��� ȣ���մϴ�.
	OnAnimationChange(m_current, &animation);

	m_elapsed = 0;
	m_current = animation;

	// �ؽ��ĸ� ������Ʈ�մϴ�.
	UpdateTexture();
}

void SpriteAnimator::SetDefaultAnimation(SpriteAnimation* animation, bool play)
{
	if (m_default == animation)
	{
		return;
	}

	// �⺻ �ִϸ��̼� ���� �̺�Ʈ�Լ��� ȣ���մϴ�.
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
	m_renderer->SetTexture(0, texture);
}

void SpriteAnimator::Transition()
{
	if (!m_renderer) return;
	if (!m_current) return;

	// ��� �ð��� �����մϴ�.
	if (!m_pause)
		m_elapsed += Time::DeltaTime() * m_speed;

	// ���� �ִϸ��̼��� �ƴѵ�, �ִϸ��̼��� ���� ���
	if (!m_current->isLoop && m_current->IsEnd(m_elapsed))
	{
		SpriteAnimation* current = m_current;
		m_current = nullptr;

		// �ִϸ��̼� ���� �̺�Ʈ�Լ��� ȣ���մϴ�.
		OnAnimationEnd();

		// OnAnimationEnd() ���� �ٸ� �ִϸ��̼��� �������� ���� ��쿡
		if (m_current == nullptr)
		{
			// �ִϸ��̼��� �������� �ʴ� �����̸� ���� �ִϸ��̼��� �״�� �����ϰ� �����մϴ�.
			if (!m_transition)
			{
				m_current = current;
				return;
			}

			// �⺻ �ִϸ��̼����� ��ȯ�մϴ�.
			PlayAnimation(m_default, true);

			// �⺻ �ִϸ��̼ǵ� �������� �ʴ´ٸ� �����մϴ�.
			if (!m_current)
			{
				return;
			}

			// ����� �ִϸ��̼��� �ؽ��ĸ� �����մϴ�.
			UpdateTexture();
		}
	}
}
