#pragma once

class SpriteAnimation
{
public:

	void AddTexture(const wstring& textureLocalPath);

	void AddTexture(const Ref<Texture>& texture);

	void ClearTextures();

public:

	size_t GetTextureCount() const;

	float GetMaxTime() const;

	float GetInverval() const;

	bool IsLoop() const;

	bool IndexOf(unsigned int index, Texture** ppTexture) const;

	bool TimeOf(float time, Texture** ppTexture) const;

	bool IsEnd(float time) const;

	__declspec(property(get = GetTextureCount)) size_t textureCount;

	__declspec(property(get = GetMaxTime)) float maxTime;

	__declspec(property(get = GetInverval)) float interval;

	__declspec(property(get = IsLoop)) bool isLoop;

public:

	std::vector<Ref<Texture>> m_textures;

	float m_interval = 0.05f;

	bool m_loop = false;
};

