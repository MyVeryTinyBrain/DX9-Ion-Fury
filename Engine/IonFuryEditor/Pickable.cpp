#include "IonFuryEditorBase.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorManager.h"

std::vector<Pickable*> Pickable::g_PickableVec;

void Pickable::Awake()
{
	m_ChildObject = CreateGameObject();
	g_PickableVec.push_back(this);
	
	//m_ChildObject->transform->position = GetGameObject()->transform->position;
	m_ChildObject->transform->parent = GetGameObject()->transform;
	m_ChildObject->transform->localPosition = Vec3(0.f, 0.f, 0.f);
	

	//m_ChildObject->AddComponent<Gizmo>();//추후 승욱이가 얘기하면 attach하는걸로

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
	
	//Q : 이렇게 하면 카메라 위치 따라 못만든다. ?? 부모를 카메라 앞에 만들었는데?? 로컬포지션 000초기화를 못했나?
	//m_ChildObject->AddComponent<Gizmo>();
}

void Pickable::Update()
{
	//if(mousebuttonkeydown)
	// vec들고와서 범위기반 for문으로 renderer들고와서 raycast실행해주기
	//걸린놈 있으면 삭제든 뭐든 명령을 내려라.
}

void Pickable::Settings(const wstring& localPathMesh, const wstring& localPathTexture)
{
	m_Renderer = m_ChildObject->AddComponent<UserMeshRenderer>();
	m_Renderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
	m_Renderer->SetTexture(0, Resource::Find(localPathTexture)->GetReferenceTo<Texture>());
}
