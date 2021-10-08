#include "stdafx.h"
#include "SpriteAnimation.h"

void SpriteAnimation::AddTexture(const wstring& textureLocalPath)
{
	Texture* texture = Resource::FindAs<Texture>(textureLocalPath);
	if (!texture)
	{
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

bool SpriteAnimation::IsLoop() const
{
	return m_loop;
}

bool SpriteAnimation::IndexOf(unsigned int index, Texture** ppTexture) const
{
	*ppTexture = nullptr;

	if (m_loop)
	{
		*ppTexture = m_textures[index % textureCount].GetPointer();
	}
	else
	{
		*ppTexture = m_textures[Clamp(index, 0, textureCount)].GetPointer();
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

bool SpriteAnimation::IsEnd(float time) const
{
	return time >= maxTime;
}
