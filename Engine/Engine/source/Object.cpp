#include "EngineBase.h"
#include "Object.h"
#include "RefData.h"

Object::Object() : BaseObject()
{
	m_refData = new RefData(this);
}

Object::Object(wstring name) : BaseObject(name)
{
	m_refData = new RefData(this);
}

Object::~Object()
{
	m_refData->SetDestroyed();

	SafeDelete(m_refData);
}

const RefData* Object::GetRefData() const
{
	return m_refData;
}
