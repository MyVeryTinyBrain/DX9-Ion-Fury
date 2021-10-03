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
	

	//m_ChildObject->AddComponent<Gizmo>();//���� �¿��̰� ����ϸ� attach�ϴ°ɷ�

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
	
	//Q : �̷��� �ϸ� ī�޶� ��ġ ���� �������. ?? �θ� ī�޶� �տ� ������µ�?? ���������� 000�ʱ�ȭ�� ���߳�?
	//m_ChildObject->AddComponent<Gizmo>();
}

void Pickable::Update()
{
	//if(mousebuttonkeydown)
	// vec���ͼ� ������� for������ renderer���ͼ� raycast�������ֱ�
	//�ɸ��� ������ ������ ���� ����� ������.
}

void Pickable::Settings(const wstring& localPathMesh, const wstring& localPathTexture)
{
	m_Renderer = m_ChildObject->AddComponent<UserMeshRenderer>();
	m_Renderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
	m_Renderer->SetTexture(0, Resource::Find(localPathTexture)->GetReferenceTo<Texture>());
}
