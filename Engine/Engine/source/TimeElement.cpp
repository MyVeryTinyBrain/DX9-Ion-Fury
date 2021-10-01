#include "EngineBase.h"
#include "TimeElement.h"

TimeElement::TimeElement(float interval)
{
    Reset();

    m_interval = interval;
}

TimeElement::~TimeElement()
{
}

void TimeElement::Reset()
{
    m_accumulated = 0;
    m_beforeTick = GetTick();
    m_deltaTime = 0;
    m_timeScale = 1;
}

void TimeElement::SetInterval(float interval)
{
    m_interval = interval;
}

float TimeElement::GetInterval() const
{
    return m_interval;
}

float TimeElement::GetAccumulated() const
{
    return m_accumulated;
}

float TimeElement::GetDeltaTime() const
{
    return m_deltaTime * m_timeScale;
}

float TimeElement::GetUnscaledDeltaTime() const
{
    return m_deltaTime;
}

void TimeElement::SetTimeScale(float timeScale)
{
    if (timeScale < 0)
        timeScale = 0;

    m_timeScale = timeScale;
}

float TimeElement::GetTimeScale() const
{
    return m_timeScale;
}

LONGLONG TimeElement::GetTickPerSeconds() const
{
    LARGE_INTEGER pf;
    QueryPerformanceFrequency(&pf);
    return pf.QuadPart;
}

LONGLONG TimeElement::GetTick() const
{
    LARGE_INTEGER pc;
    QueryPerformanceCounter(&pc);
    return pc.QuadPart;
}

UpdateTimeElement::UpdateTimeElement(float interval) : TimeElement(interval)
{
}

unsigned int UpdateTimeElement::Accumulate()
{
    // ============================================================
    // 간격 시간보다 누적 시간이 더 커지더라도 언제나 1을 반환합니다.
    // 1 이상의 정수를 반환할 때 언제나 누적 시간을 0으로 초기화합니다. 
    // 델타 타임은 누적된 시간이 바로 대입됩니다.
    // ============================================================

    LONGLONG currentTick = GetTick();

    LONGLONG elapsedTick = currentTick - m_beforeTick;

    m_beforeTick = currentTick;

    float elapsed = float(elapsedTick) / float(GetTickPerSeconds());

    m_accumulated += elapsed;

    if (m_accumulated >= m_interval)
    {
        m_deltaTime = m_accumulated;

        m_accumulated = 0;

        return 1;
    }

    return 0;
}

FixedUptateTimeElement::FixedUptateTimeElement(float interval) : TimeElement(interval)
{
}

unsigned int FixedUptateTimeElement::Accumulate()
{
    // ==================================================================================
    // 간격 시간보다 누적 시간이 커지면 누적 시간을 간격 시간으로 나눈 정수를 반환합니다.
    // 1 이상의 정수를 반환할 때 누적 시간은 간격 시간보다 작은 값으로 재설정됩니다.
    // 델타 타임은 언제나 간격 시간으로 고정됩니다.
    // ==================================================================================

    LONGLONG currentTick = GetTick();

    LONGLONG elapsedTick = currentTick - m_beforeTick;

    m_beforeTick = currentTick;

    float elapsed = float(elapsedTick) / float(GetTickPerSeconds());

    m_accumulated += elapsed;

    if (m_accumulated >= m_interval)
    {
        DWORD over = DWORD(m_accumulated / m_interval);

        m_accumulated -= over * m_interval;

        m_deltaTime = m_interval;

        return over;
    }

    return 0;
}
