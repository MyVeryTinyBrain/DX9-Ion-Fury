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

	void SetInterval(float value);

	bool IsLoop() const;

	void SetLoop(bool value);

	bool IndexOf(unsigned int index, Texture** ppTexture) const;

	bool TimeOf(float time, Texture** ppTexture) const;

	bool IsEnd(float time) const;

	__declspec(property(get = GetTextureCount)) size_t textureCount;

	__declspec(property(get = GetMaxTime)) float maxTime;

	__declspec(property(get = GetInverval, put = SetInterval)) float interval;

	__declspec(property(get = IsLoop, put = SetLoop)) bool isLoop;

private:

	std::vector<Ref<Texture>> m_textures;

	float m_interval = 0.05f;

	bool m_loop = false;
};

