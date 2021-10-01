#pragma once

#include "EngineBase.h"

#include "Ref.h"
#include "RefData.h"
#include "Object.h"

template<class T>
inline Ref<T>::Ref()
{
	m_refData = nullptr;
}

template<class T>
inline Ref<T>::Ref(RefData* refData) : Ref()
{
	if (!refData) return;

	m_refData = new RefData(*refData);
}

template<class T>
inline Ref<T>::Ref(T* pointer) : Ref()
{
	if (!pointer)
		return;

	Object* object = static_cast<Object*>(pointer);

	const RefData* pRefData = object->GetRefData();

	if (!pRefData)
		return;

	m_refData = new RefData(*pRefData);
}

template<class T>
inline Ref<T>::Ref(const Ref& other) : Ref()
{
	if (!other.m_refData) return;

	m_refData = new RefData(*other.m_refData);
}

template<class T>
template<class U>
inline Ref<T>::Ref(const Ref<U>& other) : Ref()
{
	if (!other.m_refData) return;

	U* otherPointer = other.GetPointer();
	T* cast = dynamic_cast<T*>(otherPointer);

	if (!cast)
	{
		m_refData = nullptr;
	}
	else
	{
		m_refData = new RefData(*other.m_refData);
	}
}

template<class T>
inline Ref<T>::Ref(Ref&& other)
{
	m_refData = other.m_refData;

	other.m_refData = nullptr;
}

template<class T>
inline Ref<T>::~Ref()
{
	SafeDelete(m_refData);
}

template<class T>
inline Ref<T>& Ref<T>::operator=(const Ref& other)
{
	Reset();

	if (!other.m_refData) return *this;

	m_refData = new RefData(*other.m_refData);

	return *this;
}

template<class T>
template<class U>
inline Ref<T>& Ref<T>::operator=(const Ref<U>& other)
{
	Reset();

	if (!other.m_refData) return *this;

	U* otherPointer = other.GetPointer();
	T* cast = dynamic_cast<T*>(otherPointer);

	if (!cast)
	{
		m_refData = nullptr;
	}
	else
	{
		m_refData = new RefData(*other.m_refData);
	}

	return *this;
}

template <class T>
inline Ref<T>& Ref<T>::operator = (Ref&& other)
{
	Reset();

	m_refData = other.m_refData;

	other.m_refData = nullptr;

	return *this;
}

template <class T>
template <class U>
inline Ref<T>& Ref<T>::operator = (Ref<U>&& other)
{
	Reset();

	if (!other.m_refData) return *this;

	U* otherPointer = other.GetPointer();
	T* cast = dynamic_cast<T*>(otherPointer);

	if (!cast)
	{
		m_refData = nullptr;
	}
	else
	{
		m_refData = other.m_refData;
	}

	other.m_refData = nullptr;

	return *this;
}

template<class T>
inline bool Ref<T>::operator==(const Ref& other)
{
	return GetObject() == other->GetObject();
}

template<class T>
inline bool Ref<T>::operator!=(const Ref& other)
{
	return GetObject() != other->GetObject();
}

template<class T>
template<class U>
inline bool Ref<T>::operator==(const Ref<U>& other)
{
	return GetObject() == other->GetObject();
}

template<class T>
template<class U>
inline bool Ref<T>::operator!=(const Ref<U>& other)
{
	return GetObject() != other->GetObject();
}

template<class T>
inline bool Ref<T>::operator!() const
{
	return IsNull();
}

template<class T>
inline Ref<T>::operator bool() const
{
	return !IsNull();
}

template<class T>
inline T* Ref<T>::operator->() const
{
	return GetPointer();
}

template<class T>
inline T& Ref<T>::operator*() const
{
	return GetInstance();
}

template<class T>
inline Object* Ref<T>::GetObject() const
{
	if (!m_refData)
		return nullptr;
	
	return m_refData->GetObject();
}

template<class T>
inline T* Ref<T>::GetPointer() const
{
	if (!m_refData)
		return nullptr;

	return static_cast<T*>(m_refData->GetObject());
}

template<class T>
inline T& Ref<T>::GetInstance() const
{
	T* ptr = (T*)m_refData->GetPointer();
	return *ptr;
}

template<class T>
inline size_t Ref<T>::GetRefCount() const
{
	if (!m_refData)
		return 0;
	
	return m_refData->GetRefCount();
}

template<class T>
inline void Ref<T>::Reset()
{
	SafeDelete(m_refData);
}

template<class T>
inline bool Ref<T>::IsNull() const
{
	if (!m_refData)
		return true;
	
	return m_refData->IsNull();
}
