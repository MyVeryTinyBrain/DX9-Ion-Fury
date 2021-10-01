#pragma once

#include "BaseObject.h"
#include "Ref.h"
#include "ObjectDefine.h"

class Object : public BaseObject
{
	template <class T> friend class Ref;

public:

	Object();

	Object(wstring name);

	virtual ~Object();

	template <class T>
	Ref<T> GetReferenceAs();

	template <class T>
	Ref<T> GetReferenceTo();

	DefineGetReferenceTo(Object);

protected:

	const class RefData* GetRefData() const;

protected:

	class RefData* m_refData = nullptr;
};

#include "Object.hpp"

