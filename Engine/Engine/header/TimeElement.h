#pragma once

class TimeElement
{
public:

	TimeElement(float interval);

	~TimeElement();

	// ===================================================================================
	// Accumulate 함수를 호출하면 이전 시간과 Accumulate 호출 시간 사이의 간격을 누적시킵니다.
	// 누적 시간이 간격 시간보다 커지면 업데이트를 호출해야 할 횟수를 반환하고
	// 재정의한 함수 내용에 따라 누적 시간을 재설정합니다.
	// ===================================================================================
	virtual unsigned int Accumulate() = 0;

	void Reset();

	void SetInterval(float interval);

	float GetInterval() const;

	float GetAccumulated() const;

	float GetDeltaTime() const;

	float GetUnscaledDeltaTime() const;

	void SetTimeScale(float timeScale);

	float GetTimeScale() const;

protected:

	LONGLONG GetTickPerSeconds() const;

	LONGLONG GetTick() const;

protected:

	float m_interval;

	float m_timeScale;

	float m_accumulated;

	float m_deltaTime;

	LONGLONG m_beforeTick;
};

class UpdateTimeElement : public TimeElement
{
public:
	UpdateTimeElement(float interval);

	~UpdateTimeElement() = default;

	virtual unsigned int Accumulate() override;
};

class FixedUptateTimeElement : public TimeElement
{
public:
	FixedUptateTimeElement(float interval);

	~FixedUptateTimeElement() = default;

	virtual unsigned int Accumulate() override;
};

