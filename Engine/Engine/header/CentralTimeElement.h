#pragma once

class CentralTimeElement
{
	DeclareSingletone(CentralTimeElement);

	CentralTimeElement();

	~CentralTimeElement();

public:

	void Initialize(float updateFPS, float fixedUpdateFPS);

	void Reset();

	unsigned int UpdateAccumulate();

	unsigned int FixedUpdateAccumulate();

	void SetUpdateFPS(float fps);

	void SetFixedUpdateFPS(float fps);

	float GetUpdateFPS() const;

	float GetFixedUpdateFPS() const;
	
	void SetUpdateTimeScale(float timeScale);

	void SetFixedUpdateTimeScale(float timeScale);

	float GetUpdateTimeScale() const;

	float GetFixedUpdateTimeScale() const;

	float GetUpdateDeltaTime() const;

	float GetFixedUpdateDeltaTime() const;

	float GetUnscaledUpdateDelteTime() const;

	float GetUnscaledFixedUpdateDeltaTime() const;

private:

	float m_updateTargetFPS;

	class TimeElement* m_updateTimeElement;

	float m_fixedUpdateTargetFPS;

	class TimeElement* m_fixedUpdateTimeElement;
};

