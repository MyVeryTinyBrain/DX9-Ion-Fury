#pragma once

class Collider;
class Rigidbody;

struct Contact
{
	Vec3 point;
	Vec3 normal;
	Vec3 impulse;
	float seperation;
};

class CollisionBase
{
public:

	CollisionBase(const PxContactPair* pairs, bool inverse);

	CollisionBase(const CollisionBase& other);

	CollisionBase(CollisionBase&& other) noexcept;

	virtual ~CollisionBase();

	CollisionBase& operator = (const CollisionBase& other);

	CollisionBase& operator = (CollisionBase&& other) noexcept;

public:

	Collider* GetToCollider() const;

	Collider* GetFromCollider() const;

	unsigned int GetContactCount() const;

	Contact GetContact(unsigned int index) const;

	__declspec(property(get = GetToCollider)) Collider* toCollider;

	__declspec(property(get = GetFromCollider)) Collider* fromCollider;

	__declspec(property(get = GetContactCount)) unsigned int contactCount;

private:

	// ����) �浹���� �ݶ��̴��Դϴ�.
	Collider* m_to = nullptr;

	// ���) �浹�� �ݶ��̴��Դϴ�.
	Collider* m_from = nullptr;

	unsigned int m_numContacts = 0;

	PxContactPairPoint* m_contacts = nullptr;
};

class TriggerBase
{
public:

	TriggerBase(Collider* to, Collider* from);

private:

	Collider* m_to = nullptr;

	Collider* m_from = nullptr;
};

class CollisionEnter : public CollisionBase
{
public:

	inline CollisionEnter(const PxContactPair* pairs, bool inverse) : CollisionBase(pairs, inverse) {}

	inline CollisionEnter(const CollisionEnter& other) : CollisionBase(other) {}

	inline CollisionEnter(CollisionEnter&& other) noexcept : CollisionBase(other) {}

	inline virtual ~CollisionEnter() = default;

	inline CollisionEnter& operator = (const CollisionEnter& other)
	{
		CollisionBase::operator=(other);
		return *this;
	}

	inline CollisionEnter& operator = (CollisionEnter&& other) noexcept
	{
		CollisionBase::operator=(other);
		return *this;
	}
};

class CollisionStay : public CollisionBase
{
public:

	inline CollisionStay(const PxContactPair* pairs, bool inverse) : CollisionBase(pairs, inverse) {}

	inline CollisionStay(const CollisionStay& other) : CollisionBase(other) {}

	inline CollisionStay(CollisionStay&& other) noexcept : CollisionBase(other) {}

	inline virtual ~CollisionStay() = default;

	inline CollisionStay& operator = (const CollisionStay& other)
	{
		CollisionBase::operator=(other);
		return *this;
	}

	inline CollisionStay& operator = (CollisionStay&& other) noexcept
	{
		CollisionBase::operator=(other);
		return *this;
	}
};

class CollisionExit
{
public:

	CollisionExit(PxShape* from, PxShape* exit) : m_from((Collider*)from->userData), m_exit((Collider*)exit) {}

public:

	Collider* GetFromCollider() const;

	Collider* GetExitCollider() const;

	__declspec(property(get = GetFromCollider)) Collider* fromCollider;

	__declspec(property(get = GetExitCollider)) Collider* exitCollider;

private:

	// ����) exit�� ������ �ݶ��̴��Դϴ�.
	Collider* m_from = nullptr;

	// ���) from ���Լ� ������ �ݶ��̴��Դϴ�.
	Collider* m_exit = nullptr;
};

class TriggerEnter : public TriggerBase
{

};

class TriggerStay : public TriggerBase
{

};

class TriggerExit : public TriggerBase
{

};

