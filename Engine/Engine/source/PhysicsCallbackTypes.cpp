#include "EngineBase.h"
#include "PhysicsCallbackTypes.h"
#include "PhysicsDefines.h"

CollisionBase::CollisionBase(const PxContactPair* pairs, bool inverse)
{
	// =====================================================================================================
	// pairs�� normal ������ shape1 -> shape0 �� ���ϴ� �����Դϴ�.
	// ���� shape1�� �浹�޴� ������� �����ϸ� shape1 -> shape0 ���� ���ϴ� ��� �����̹Ƿ� ���� �����ϴ�.
	// �ݴ��� ����� shape0�� �浹�޴� ������� �Ҷ���, shape1 -> shape0 �� ��� ������ �Ųٷ� ������ ����մϴ�.
	// inverse == false �϶� shape1 -> shape0 (shape0�� �浹 ���ϴ� ���) ������ ����ϰ�,
	// inverse == true  �϶� shape0 -> shape1 (shape1�� �浹 ���ϴ� ���) �������� ����մϴ�.
	// =====================================================================================================

	m_numContacts = pairs->contactCount;
	m_contacts = new PxContactPairPoint[m_numContacts];
	pairs->extractContacts(m_contacts, m_numContacts);

	if (!inverse)
	{
		m_to = (Collider*)pairs->shapes[0]->userData;
		m_from = (Collider*)pairs->shapes[1]->userData;
	}
	else
	{
		m_to = (Collider*)pairs->shapes[1]->userData;
		m_from = (Collider*)pairs->shapes[0]->userData;
		for (unsigned int i = 0; i < m_numContacts; ++i)
		{
			m_contacts[i].normal *= -1;
		}
	}
}

CollisionBase::CollisionBase(const CollisionBase& other)
{
	m_to = other.m_to;
	m_from = other.m_from;
	m_numContacts = other.m_numContacts;
	m_contacts = new PxContactPairPoint[m_numContacts];
	memcpy(m_contacts, other.m_contacts, sizeof(PxContactPairPoint) * m_numContacts);
}

CollisionBase::CollisionBase(CollisionBase&& other) noexcept
{
	m_to = other.m_to;
	m_from = other.m_from;
	m_numContacts = other.m_numContacts;
	m_contacts = other.m_contacts;

	other.m_contacts = nullptr;
}

CollisionBase::~CollisionBase()
{
	SafeDeleteArray(m_contacts);
}

CollisionBase& CollisionBase::operator=(const CollisionBase& other)
{
	SafeDeleteArray(m_contacts);

	m_to = other.m_to;
	m_from = other.m_from;
	m_numContacts = other.m_numContacts;
	m_contacts = new PxContactPairPoint[m_numContacts];
	memcpy(m_contacts, other.m_contacts, sizeof(PxContactPairPoint) * m_numContacts);

	return *this;
}

CollisionBase& CollisionBase::operator=(CollisionBase&& other) noexcept
{
	SafeDeleteArray(m_contacts);

	m_to = other.m_to;
	m_from = other.m_from;
	m_numContacts = other.m_numContacts;
	m_contacts = other.m_contacts;

	other.m_contacts = nullptr;

	return *this;
}

Collider* CollisionBase::GetToCollider() const
{
	return m_to;
}

Collider* CollisionBase::GetFromCollider() const
{
	return m_from;
}

unsigned int CollisionBase::GetContactCount() const
{
	return m_numContacts;
}

Contact CollisionBase::GetContact(unsigned int index) const
{
	Contact contact;
	contact.point = FromPxVec3(m_contacts[index].position);
	contact.normal = FromPxVec3(m_contacts[index].normal);
	contact.impulse = FromPxVec3(m_contacts[index].impulse);
	return contact;
}

TriggerBase::TriggerBase(Collider* to, Collider* from)
{
	m_to = to;
	m_from = from;
}

Collider* CollisionExit::GetFromCollider() const
{
	return m_from;
}

Collider* CollisionExit::GetExitCollider() const
{
	return m_exit;
}
