#include "shared_stdafx.h"
#include "Numbers.h"
#include "Number.h"

void Numbers::Awake()
{
	auto oneObj = CreateGameObjectToChild(transform);
	oneObj->transform->localScale = Vec2::one();
	oneObj->transform->localPosition = Vec2(1, 0);
	m_compNum[NumOne] = oneObj->AddComponent<Number>();

	auto tenObj = CreateGameObjectToChild(transform);
	tenObj->transform->localScale = Vec2::one();
	tenObj->transform->localPosition = Vec2(0, 0);
	m_compNum[NumTen] = tenObj->AddComponent<Number>();

	auto hundredObj = CreateGameObjectToChild(transform);
	hundredObj->transform->localScale = Vec2::one();
	hundredObj->transform->localPosition = Vec2(-1, 0);
	m_compNum[NumHundred] = hundredObj->AddComponent<Number>();

	number = 999;
}

void Numbers::SetNumber(unsigned int number)
{
	if (number > 999)
	{
		number = 999;
	}

	m_number = number;

	unsigned int _100 = number / 100;
	number -= _100 * 100;

	unsigned int _10 = number / 10;
	number -= _10 * 10;

	unsigned int _1 = number;

	switch (m_alignment)
	{
		case Alignment::Left:
			ShowNumberToLeft(_100, _10, _1);
			break;
		case Alignment::Right:
			ShowNumberToRight(_100, _10, _1);
			break;
	}
}

unsigned int Numbers::GetNumber() const
{
	return m_number;
}

Numbers::Alignment Numbers::GetAlignment() const
{
	return m_alignment;
}

void Numbers::SetAlignment(Numbers::Alignment alignment)
{
	m_alignment = alignment;
}

void Numbers::ShowNumberToLeft(unsigned int _100, unsigned int _10, unsigned int _1)
{
	if (_100 > 0)
	{
		m_compNum[NumOne]->number = _1;
		m_compNum[NumTen]->number = _10;
		m_compNum[NumHundred]->number = _100;

		m_compNum[NumOne]->gameObject->activeSelf = true;
		m_compNum[NumTen]->gameObject->activeSelf = true;
		m_compNum[NumHundred]->gameObject->activeSelf = true;
	}
	else if (_10 > 0)
	{
		m_compNum[NumTen]->number = _1;
		m_compNum[NumHundred]->number = _10;

		m_compNum[NumOne]->gameObject->activeSelf = false;
		m_compNum[NumTen]->gameObject->activeSelf = true;
		m_compNum[NumHundred]->gameObject->activeSelf = true;
	}
	else
	{
		m_compNum[NumHundred]->number = _1;

		m_compNum[NumOne]->gameObject->activeSelf = false;
		m_compNum[NumTen]->gameObject->activeSelf = false;
		m_compNum[NumHundred]->gameObject->activeSelf = true;
	}
}

void Numbers::ShowNumberToRight(unsigned int _100, unsigned int _10, unsigned int _1)
{
	if (_100 > 0)
	{
		m_compNum[NumOne]->number = _1;
		m_compNum[NumTen]->number = _10;
		m_compNum[NumHundred]->number = _100;

		m_compNum[NumOne]->gameObject->activeSelf = true;
		m_compNum[NumTen]->gameObject->activeSelf = true;
		m_compNum[NumHundred]->gameObject->activeSelf = true;
	}
	else if (_10 > 0)
	{
		m_compNum[NumOne]->number = _1;
		m_compNum[NumTen]->number = _10;

		m_compNum[NumOne]->gameObject->activeSelf = true;
		m_compNum[NumTen]->gameObject->activeSelf = true;
		m_compNum[NumHundred]->gameObject->activeSelf = false;
	}
	else
	{
		m_compNum[NumOne]->number = _1;

		m_compNum[NumOne]->gameObject->activeSelf = true;
		m_compNum[NumTen]->gameObject->activeSelf = false;
		m_compNum[NumHundred]->gameObject->activeSelf = false;
	}
}
