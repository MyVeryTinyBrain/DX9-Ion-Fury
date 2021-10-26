#pragma once

class MainSceneComponent : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	void FadeIn(float time = 0.5f);

	void FadeOut(float time = 0.5f);

	void SetFadeAlpah(float value);

	float GetFadeAlpha() const;

	void AsyncResourceLoad();

private:

	UserMeshRenderer* m_pressAnyKeyRenderer = nullptr;

	bool m_readyToChangeScene = false;

	// Loading thread

	std::thread m_resourceLoadThread;

	static bool g_loaded;

	// Fade effect

	GameObject* m_fadeImageObj = nullptr;

	UserMeshRenderer* m_fadeImageRenderer = nullptr;

	enum { FADE_STEP = 64, FADE_BEGIN = 0, FADE_END = FADE_STEP - 1 };

	Texture* m_fadeTexture[FADE_STEP] = {};

	float m_fadeAlpha = 1.0f;

	float m_targetFadeAlpha = 1.0f;

	float m_fadeSpeed = 1.0f;
};

