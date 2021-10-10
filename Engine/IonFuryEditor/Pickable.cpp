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

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
}

void Pickable::Update()
{
	if (Input::GetKeyDown(Key::LeftMouse))
		Pick();
}

void Pickable::OnDestroy()
{
	auto it = FindInContainer(g_PickableVec, this);
	if (it != g_PickableVec.end())
		g_PickableVec.erase(it);
}

void Pickable::Settings(const wstring& localPathMesh, const wstring& localPathTexture)
{
	m_Renderer = m_ChildObject->AddComponent<UserMeshRenderer>();
	m_Renderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
	m_Renderer->SetTexture(0, Resource::FindAs<Texture>(localPathTexture));
	//m_Renderer->SetTexture(0, Resource::Find(localPathTexture)->GetReferenceTo<Texture>());
}

Pickable* Pickable::Pick()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;

	for (auto pickable : g_PickableVec)
	{
		UserMeshRenderer* Renderer = pickable->GetRenderer();

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			EditorManager::GetInstance()->GetGizmo()->Attach(pickable->transform);
			return pickable;
		}
	}

	return nullptr;
}

//void Pickable::PickDelete()
//{
	//Gizmo* Giz = EditorManager::GetInstance()->GetGizmo();
	//GameObject* Obj = Giz->GetSelectedObject()
	//	->gameObject->Destroy();
//}
