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
	// 안전상의 이유로 소멸자에서 한 번 더 Destroy() 함수를 호출합니다.
	// 만약 Destroy()가 호출되지 않은 상태에서 소멸자가 호출되면 참조 데이터 타입의 isDestroy 플래그가 켜져있지 않은 상태로 소멸됩니다.
	// 이 경우에는 참조 카운터가 0이 되어도 참조 데이터 타입에서 동적생성된 메모리는 반환되지 않기 때문입니다.
	// 그리고 Destory() 함수는 한 번 호출되면 그 이후에는 여러 번 호출해도 문제가 없으므로 이 방법을 사용합니다.
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

	// 부모 클래스인 Object 클래스에서 m_refData를 삭제합니다.
	// 이미 삭제된 m_refData를 참조할 수 있으므로 검사 후 함수를 호출합니다.
	if (m_refData)
	{
		m_refData->SetDestroyed();
	}
}

bool SceneObject::IsShouldDestroy() const
{
	return m_shouldDestroy;
}
