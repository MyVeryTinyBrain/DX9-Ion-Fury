#include "EngineBase.h"
#include "CentralTimeElement.h"
#include "TimeElement.h"

ImplementSingletone(CentralTimeElement)

CentralTimeElement::CentralTimeElement()
{
	m_updateTimeElement = new UpdateTimeElement(1.0f / 60.0f);
	SetUpdateFPS(60.0f);

	m_fixedUpdateTimeElement = new FixedUptateTimeElement(1.0f / 60.0f);
	SetFixedUpdateFPS(60.0f);
}

CentralTimeElement::~CentralTimeElement()
{
	SafeDelete(m_updateTimeElement);
	SafeDelete(m_fixedUpdateTimeElement);
}

void CentralTimeElement::Initialize(float updateFPS, float fixedUpdateFPS)
{
	SetUpdateFPS(updateFPS);
	SetFixedUpdateFPS(fixedUpdateFPS);
}

void CentralTimeElement::Reset()
{
	m_updateTimeElement->Reset();
	m_fixedUpdateTimeElement->Reset();
}

unsigned int CentralTimeElement::UpdateAccumulate()
{
	return m_updateTimeElement->Accumulate();
}

unsigned int CentralTimeElement::FixedUpdateAccumulate()
{
	return m_fixedUpdateTimeElement->Accumulate();
}

void CentralTimeElement::SetUpdateFPS(float fps)
{
	if (fps < 0) fps = FLT_MAX;

	m_updateTimeElement->SetInterval(1.0f / fps);
	m_updateTargetFPS = fps;
}

void CentralTimeElement::SetFixedUpdateFPS(float fps)
{
	if (fps < 0) fps = FLT_MAX;

	m_fixedUpdateTimeElement->SetInterval(1.0f / fps);
	m_fixedUpdateTargetFPS = fps;
}

float CentralTimeElement::GetUpdateFPS() const
{
	return m_updateTargetFPS;
}

float CentralTimeElement::GetFixedUpdateFPS() const
{
	return m_fixedUpdateTargetFPS;
}

void CentralTimeElement::SetUpdateTimeScale(float timeScale)
{
	m_updateTimeElement->SetTimeScale(timeScale);
}

void CentralTimeElement::SetFixedUpdateTimeScale(float timeScale)
{
	m_fixedUpdateTimeElement->SetTimeScale(timeScale);
}

float CentralTimeElement::GetUpdateTimeScale() const
{
	return m_updateTimeElement->GetTimeScale();
}

float CentralTimeElement::GetFixedUpdateTimeScale() const
{
	return m_fixedUpdateTimeElement->GetTimeScale();
}

float CentralTimeElement::GetUpdateDeltaTime() const
{
	return m_updateTimeElement->GetDeltaTime();
}

float CentralTimeElement::GetFixedUpdateDeltaTime() const
{
	return m_fixedUpdateTimeElement->GetDeltaTime();
}

float CentralTimeElement::GetUnscaledUpdateDelteTime() const
{
	return m_updateTimeElement->GetUnscaledDeltaTime();
}

float CentralTimeElement::GetUnscaledFixedUpdateDeltaTime() const
{
	return m_fixedUpdateTimeElement->GetUnscaledDeltaTime();
}

float CentralTimeElement::GetUpdateAccumulated() const
{
	return m_updateTimeElement->GetAccumulated();
}

float CentralTimeElement::GetFixedUpdateAccumulated() const
{
	return m_fixedUpdateTimeElement->GetAccumulated();
}
