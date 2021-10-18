#pragma once

class Number : public Component
{
	OverrideComponentFunction(Awake);

public:

	void SetNumber(unsigned int digit);

	unsigned int GetNumber() const;

	__declspec(property(get = GetNumber, put = SetNumber)) unsigned int number;

private:

	Texture* m_nums[10] = {};

	UserMeshRenderer* m_renderer = nullptr;

	int m_numIndex = 0;
};

