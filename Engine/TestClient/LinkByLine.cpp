#include "stdafx.h"
#include "LinkByLine.h"

void LinkByLine::Render()
{
	Line::DrawLine(m_targetA->position, m_targetB->position, Color::white(), 10);
}

void LinkByLine::OnWake()
{
	int forTest = 0;
}

void LinkByLine::OnSleep()
{
	int forTest = 0;
}

void LinkByLine::SetTargetA(Ref<Transform> target)
{
	m_targetA = target;
}

void LinkByLine::SetTargetB(Ref<Transform> target)
{
	m_targetB = target;
}
