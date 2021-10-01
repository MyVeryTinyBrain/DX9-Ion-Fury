#include "EngineBase.h"
#include "GlobalTime.h"
#include "CentralTimeElement.h"

void Time::SetTimeScale(float timeScale)
{
	CentralTimeElement::GetInstance()->SetUpdateTimeScale(timeScale);
}

void Time::SetFixedTimeScale(float timeScale)
{
	CentralTimeElement::GetInstance()->SetFixedUpdateTimeScale(timeScale);
}

float Time::TimeScale()
{
	return CentralTimeElement::GetInstance()->GetUpdateTimeScale();
}

float Time::FixedTimeScale()
{
	return CentralTimeElement::GetInstance()->GetFixedUpdateTimeScale();
}

float Time::DeltaTime()
{
	return CentralTimeElement::GetInstance()->GetUpdateDeltaTime();
}

float Time::FixedDeltaTime()
{
	return CentralTimeElement::GetInstance()->GetFixedUpdateDeltaTime();
}

float Time::UnscaledDelteTime()
{
	return CentralTimeElement::GetInstance()->GetUnscaledUpdateDelteTime();
}

float Time::UnscaledFixedDeltaTime()
{
	return CentralTimeElement::GetInstance()->GetUnscaledFixedUpdateDeltaTime();
}
