#pragma once

class Number;

class Numbers : public Component
{
public:

	enum class Alignment { Left, Right };

private:

	OverrideComponentFunction(Awake);

public:

	void SetNumber(unsigned int number);

	unsigned int GetNumber() const;

	Alignment GetAlignment() const;

	void SetAlignment(Alignment alignment);

	__declspec(property(get = GetNumber, put = SetNumber)) unsigned int number;

	__declspec(property(get = GetAlignment, put = SetAlignment)) Alignment alignment;

private:

	void ShowNumberToLeft(unsigned int _100, unsigned int _10, unsigned int _1);

	void ShowNumberToRight(unsigned int _100, unsigned int _10, unsigned int _1);

private:

	enum { NumOne = 0 };
	enum { NumTen = 1 };
	enum { NumHundred = 2 };

	Number* m_compNum[3] = {};

	int m_number = 999;

	Alignment m_alignment = Alignment::Left;
};

