#pragma once

class BaseObject
{
public:

	BaseObject() = default;

	BaseObject(wstring name);

	virtual ~BaseObject() = default;

	void SetName(const wstring& name);

	const wstring& GetName() const;

	__declspec(property(get = GetName, put = SetName)) const wstring& name;

private:

	wstring m_name = L"";
};

