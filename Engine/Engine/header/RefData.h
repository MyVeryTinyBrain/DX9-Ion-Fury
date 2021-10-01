#pragma once

#ifdef GetObject
#undef GetObject
#endif

class RefData
{
public:

	explicit RefData(class Object* pObject);
	
	explicit RefData(const RefData& other);
	
	~RefData();

	RefData& operator = (const RefData& other);

	bool operator == (const RefData& other) const;

	bool operator != (const RefData& other) const;

	bool operator ! () const;

	operator bool () const;

	Object* operator -> () const;

	class Object* GetObject() const;

	void* GetPointer() const;

	size_t GetRefCount() const;

	void Reset();

	// ==============================================================================
	// m_pObject 를 삭제하기 전에 반드시 이 함수를 호출해야 합니다.
	// 이 함수는 m_pIsDestroyed 플래그를 True로 변경합니다.
	// 만약 이 함수를 부르지 않고 m_pObject 를 삭제했다면
	// 모든 참조가 끝난 시점에도 m_pRefCount, m_pIsDestroyedrk 들이 소멸되지 않습니다.
	// ==============================================================================
	void SetDestroyed();

	bool IsNull() const;

private:

	class Object* m_pObject = nullptr;

	size_t* m_pRefCount = nullptr;

	bool* m_pIsDestroyed = nullptr;
};
