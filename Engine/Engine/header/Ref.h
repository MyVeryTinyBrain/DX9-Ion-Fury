#pragma once

#ifdef GetObject
#undef GetObject
#endif

template <class T>
class Ref
{
	template <class U> friend class Ref;

public:

	explicit Ref();

	explicit Ref(class RefData* refData);

	Ref(T* pointer);

	Ref(const Ref& other);

	template <class U>
	Ref(const Ref<U>& other);

	Ref(Ref&& other);

	~Ref();

	Ref& operator = (const Ref& other);

	template <class U>
	Ref& operator = (const Ref<U>& other);

	Ref& operator = (Ref&& other);

	template <class U>
	Ref& operator = (Ref<U>&& other);

	bool operator == (const Ref& other);

	bool operator != (const Ref& other);

	template <class U>
	bool operator == (const Ref<U>& other);

	template <class U>
	bool operator != (const Ref<U>& other);

	bool operator ! () const;

	operator bool() const;

	T* operator -> () const;

	T& operator * () const;

	class Object* GetObject() const;

	T* GetPointer() const;

	T& GetInstance() const;

	size_t GetRefCount() const;

	void Reset();

	bool IsNull() const;

private:

	class RefData* m_refData;
};

#include "Ref.hpp"
