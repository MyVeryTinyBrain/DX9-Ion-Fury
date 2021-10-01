#include "EngineBase.h"
#include "BaseObject.h"

BaseObject::BaseObject(wstring name)
{
	m_name = name;
}

void BaseObject::SetName(const wstring& name)
{
	m_name = name;
}

const wstring& BaseObject::GetName() const
{
	return m_name;
}
