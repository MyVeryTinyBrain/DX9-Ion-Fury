#include "EngineBase.h"
#include "SceneObject.h"
#include "RefData.h"

SceneObject::SceneObject() : Object()
{
}

SceneObject::SceneObject(wstring name) : Object(name)
{
}

SceneObject::~SceneObject()
{
	// =========================================================================================================================
	// �������� ������ �Ҹ��ڿ��� �� �� �� Destroy() �Լ��� ȣ���մϴ�.
	// ���� Destroy()�� ȣ����� ���� ���¿��� �Ҹ��ڰ� ȣ��Ǹ� ���� ������ Ÿ���� isDestroy �÷��װ� �������� ���� ���·� �Ҹ�˴ϴ�.
	// �� ��쿡�� ���� ī���Ͱ� 0�� �Ǿ ���� ������ Ÿ�Կ��� ���������� �޸𸮴� ��ȯ���� �ʱ� �����Դϴ�.
	// �׸��� Destory() �Լ��� �� �� ȣ��Ǹ� �� ���Ŀ��� ���� �� ȣ���ص� ������ �����Ƿ� �� ����� ����մϴ�.
	// =========================================================================================================================
	Destroy();
}

void SceneObject::Destroy()
{
	if (m_shouldDestroy) return;

	m_shouldDestroy = true;

	OnBeforeDestroy();

	OnDestroy();
	
	OnDestroyCallback(this);

	// �θ� Ŭ������ Object Ŭ�������� m_refData�� �����մϴ�.
	// �̹� ������ m_refData�� ������ �� �����Ƿ� �˻� �� �Լ��� ȣ���մϴ�.
	if (m_refData)
	{
		m_refData->SetDestroyed();
	}
}

bool SceneObject::IsShouldDestroy() const
{
	return m_shouldDestroy;
}
