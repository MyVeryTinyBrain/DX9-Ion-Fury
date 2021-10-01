#pragma once

class TimeElement
{
public:

	TimeElement(float interval);

	~TimeElement();

	// ===================================================================================
	// Accumulate �Լ��� ȣ���ϸ� ���� �ð��� Accumulate ȣ�� �ð� ������ ������ ������ŵ�ϴ�.
	// ���� �ð��� ���� �ð����� Ŀ���� ������Ʈ�� ȣ���ؾ� �� Ƚ���� ��ȯ�ϰ�
	// �������� �Լ� ���뿡 ���� ���� �ð��� �缳���մϴ�.
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

