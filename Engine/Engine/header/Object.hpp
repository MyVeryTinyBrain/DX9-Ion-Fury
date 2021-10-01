#pragma once

#include "EngineBase.h"

#include "Object.h"

template <class T>
inline class Ref<T> Object::GetReferenceAs()
{
	Object* object = m_refData->GetObject();
	T* cast = dynamic_cast<T*>(object);

	if (cast)
	{
		return Ref<T>(m_refData);
	}
	else
	{
		return Ref<T>();
	}
}

template<class T>
inline Ref<T> Object::GetReferenceTo()
{
	return Ref<T>(m_refData);
}


