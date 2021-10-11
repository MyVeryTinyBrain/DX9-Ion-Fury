#include "IonFuryEditorBase.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorManager.h"

std::vector<Pickable*> Pickable::g_PickableVec;

std::vector<Pickable*> Pickable::g_MapVec;
std::vector<Pickable*> Pickable::g_TriggerVec;
std::vector<Pickable*> Pickable::g_MonsterVec;

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

	switch (m_Type)
	{
	case Type::Map:
		it = FindInContainer(g_MapVec, this);
		if (it != g_MapVec.end())
			g_MapVec.erase(it);
		break;
	case Type::Monster:
		it = FindInContainer(g_MonsterVec, this);
		if (it != g_MonsterVec.end())
			g_MonsterVec.erase(it);
		break;
	case Type::Trigger:
		it = FindInContainer(g_TriggerVec, this);
		if (it != g_TriggerVec.end())
			g_TriggerVec.erase(it);
		break;
	}
}

void Pickable::Settings(bool ColliderExistence, const wstring& localPathMesh, const wstring& localPathTexture)
{
	m_ColliderExistence = ColliderExistence;
	m_Renderer = m_ChildObject->AddComponent<UserMeshRenderer>();
	m_Renderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
	m_Renderer->SetTexture(0, Resource::FindAs<Texture>(localPathTexture));
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
			EditorManager::GetInstance()->GetGizmo()->Attach(pickable->GetGameObject()->transform);
			return pickable;
		}
	}

	return nullptr;
}

void Pickable::PushInVector(Type type)
{
	m_Type = type;
	switch (m_Type)
	{
	case Type::Map:
		g_MapVec.push_back(this);
		break;
	case Type::Monster:
		g_MonsterVec.push_back(this);
		break;
	case Type::Trigger:
		g_TriggerVec.push_back(this);
		break;
	}
}
