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
	// m_pObject �� �����ϱ� ���� �ݵ�� �� �Լ��� ȣ���ؾ� �մϴ�.
	// �� �Լ��� m_pIsDestroyed �÷��׸� True�� �����մϴ�.
	// ���� �� �Լ��� �θ��� �ʰ� m_pObject �� �����ߴٸ�
	// ��� ������ ���� �������� m_pRefCount, m_pIsDestroyedrk ���� �Ҹ���� �ʽ��ϴ�.
	// ==============================================================================
	void SetDestroyed();

	bool IsNull() const;

private:

	class Object* m_pObject = nullptr;

	size_t* m_pRefCount = nullptr;

	bool* m_pIsDestroyed = nullptr;
};
