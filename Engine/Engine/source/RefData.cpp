#include "EngineBase.h"
#include "RefData.h"
#include "Object.h"

RefData::RefData(Object* pObject)
{
	if (!pObject) return;

	m_pObject = pObject;
	m_pRefCount = new size_t(0);
	m_pIsDestroyed = new bool(false);
}

RefData::RefData(const RefData& other)
{
	if (!other.m_pObject) return;

	m_pObject = other.m_pObject;
	m_pRefCount = other.m_pRefCount;
	m_pIsDestroyed = other.m_pIsDestroyed;

	++(*m_pRefCount);
}

RefData::~RefData()
{
	if (!m_pObject) return;

	auto& refCount = *m_pRefCount;
	auto& isDestroyed = *m_pIsDestroyed;

	if (refCount == 0)
	{
		if (isDestroyed)
		{
			SafeDelete(m_pRefCount);
			SafeDelete(m_pIsDestroyed);
		}
	}
	else
	{
		--(*m_pRefCount);
	}

	m_pObject = nullptr;
	m_pRefCount = nullptr;
	m_pIsDestroyed = nullptr;
}

RefData& RefData::operator=(const RefData& other)
{
	Reset();

	if (!other.m_pObject) return *this;

	m_pObject = other.m_pObject;
	m_pRefCount = other.m_pRefCount;
	m_pIsDestroyed = other.m_pIsDestroyed;

	++(*m_pRefCount);

	return *this;
}

bool RefData::operator==(const RefData& other) const
{
	return m_pObject == other.m_pObject;
}

bool RefData::operator!=(const RefData& other) const
{
	return m_pObject != other.m_pObject;
}

bool RefData::operator!() const
{
	return IsNull();
}

RefData::operator bool() const
{
	return !IsNull();
}

Object* RefData::operator->() const
{
	return GetObject();
}

Object* RefData::GetObject() const
{
	if (*m_pIsDestroyed)
		return nullptr;

	return m_pObject;
}

void* RefData::GetPointer() const
{
	if (*m_pIsDestroyed)
		return nullptr;

	return static_cast<void*>(m_pObject);
}

size_t RefData::GetRefCount() const
{
	return *m_pRefCount;
}

void RefData::Reset()
{
	if (!m_pObject) return;
	if (!m_pRefCount) return;

	--(*m_pRefCount);

	m_pObject = nullptr;
	m_pRefCount = nullptr;
	m_pIsDestroyed = nullptr;
}

void RefData::SetDestroyed()
{
	(*m_pIsDestroyed) = true;
}

bool RefData::IsNull() const
{
	if (!m_pObject)
		return true;
	
	return (*m_pIsDestroyed);
}
