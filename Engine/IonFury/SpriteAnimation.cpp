#include "stdafx.h"
#include "SpriteAnimation.h"

void SpriteAnimation::AddTexture(const wstring& textureLocalPath)
{
	Texture* texture = Resource::FindAs<Texture>(textureLocalPath);
	if (!texture)
	{
		wcout << L"Error(SpriteAnimation::AddTexture): " << textureLocalPath << endl;
		return;
	}

	AddTexture(texture);
}

void SpriteAnimation::AddTexture(const Ref<Texture>& texture)
{
	m_textures.push_back(texture);
}

void SpriteAnimation::ClearTextures()
{
	m_textures.clear();
}

size_t SpriteAnimation::GetTextureCount() const
{
	return m_textures.size();
}

float SpriteAnimation::GetMaxTime() const
{
	return m_textures.size() * m_interval;
}

float SpriteAnimation::GetInverval() const
{
	return m_interval;
}

void SpriteAnimation::SetInterval(float value)
{
	m_interval = value;
}

bool SpriteAnimation::IsLoop() const
{
	return m_loop;
}

void SpriteAnimation::SetLoop(bool value)
{
	m_loop = value;
}

bool SpriteAnimation::IndexOf(unsigned int index, Texture** ppTexture) const
{
	*ppTexture = nullptr;

	if (textureCount == 0)
	{
		return false;
	}

	if (m_loop)
	{
		auto texture = m_textures[index % textureCount];
		if (texture)
		{
			*ppTexture = texture.GetPointer();
		}
	}
	else
	{
		// Clamp 함수의 결과는 a <= v <= b 입니다.
		auto texture = m_textures[unsigned int(Clamp(float(index), 0, float(textureCount - 1)))];
		if (texture)
		{
			*ppTexture = texture.GetPointer();
		}
	}

	if (!m_loop && index >= textureCount)
	{
		return false;
	}

	return true;
}

bool SpriteAnimation::TimeOf(float time, Texture** ppTexture) const
{
	time = Clamp(time, 0, FLT_MAX);

	float percent = time / maxTime;
	float fIndex = percent * textureCount;
	unsigned int index = int(fIndex);

	return IndexOf(index, ppTexture);
}

unsigned int SpriteAnimation::TimeToIndex(float time) const
{
	if (time < 0)
	{
		time = 0;
	}

	float percent = time / maxTime;
	float fIndex = percent * textureCount;
	unsigned int index = int(fIndex);

	if (!m_loop && index >= textureCount)
	{
		index = unsigned int(textureCount - 1);
	}

	return index;
}

bool SpriteAnimation::IsEnd(float time) const
{
	return time >= maxTime;
}

void SpriteAnimation::FitIntervalToTime(float time)
{
	if (textureCount == 0)
	{
		return;
	}

	m_interval = time / textureCount;
}
