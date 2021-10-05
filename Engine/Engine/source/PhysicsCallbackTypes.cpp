#include "EngineBase.h"
#include "PhysicsCallbackTypes.h"
#include "PhysicsDefines.h"

CollisionBase::CollisionBase(const PxContactPair* pairs, bool inverse)
{
	// =====================================================================================================
	// pairs의 normal 방향은 shape1 -> shape0 로 향하는 방향입니다.
	// 따라서 shape1을 충돌받는 대상으로 설정하면 shape1 -> shape0 으로 향하는 노멀 방향이므로 문제 없습니다.
	// 반대의 경우인 shape0을 충돌받는 대상으로 할때는, shape1 -> shape0 인 노멀 방향을 거꾸로 뒤집어 사용합니다.
	// inverse == false 일때 shape1 -> shape0 (shape0이 충돌 당하는 대상) 설정을 사용하고,
	// inverse == true  일때 shape0 -> shape1 (shape1이 충돌 당하는 대상) 설정으로 사용합니다.
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
