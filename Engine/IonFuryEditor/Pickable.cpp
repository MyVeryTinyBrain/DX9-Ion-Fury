#include "IonFuryEditorBase.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorManager.h"
#include "EditorEnum.h"

std::vector<Pickable*> Pickable::g_PickableVec;

std::vector<Pickable*> Pickable::g_MapVec;
std::vector<Pickable*> Pickable::g_TriggerVec;
std::vector<Pickable*> Pickable::g_EventVec;

void Pickable::Awake()
{
	m_ChildObject = CreateGameObject();
	g_PickableVec.push_back(this);

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
	case Type::EventObject:
		it = FindInContainer(g_EventVec, this);
		if (it != g_EventVec.end())
			g_EventVec.erase(it);
		break;
	case Type::Trigger:
		it = FindInContainer(g_TriggerVec, this);
		if (it != g_TriggerVec.end())
			g_TriggerVec.erase(it);
		break;
	}

	DeleteMesh();
}

void Pickable::Settings(Vec2 UVScale, COMBOBOX comboBox, const wstring& localPathTexture, bool ColliderExistence)
{
	m_Renderer = m_ChildObject->AddComponent<UserMeshRenderer>();

	SetMesh(comboBox);
	m_Mesh->SetUVScale(UVScale);
	m_Renderer->SetTexture(0, Resource::FindAs<Texture>(localPathTexture));
	m_CollisionExistence = ColliderExistence;
}

void Pickable::SetMesh(COMBOBOX comboBox)
{
	DeleteMesh();

	switch (comboBox)
	{
	case COMBOBOX::Cube:
		m_Mesh = UserMesh::CreateUnmanaged<CubeUserMesh>();
		break;
	case COMBOBOX::Cyilinder:
		m_Mesh = UserMesh::CreateUnmanaged<CyilinderUserMesh>();
		break;
	case COMBOBOX::Quad:
		m_Mesh = UserMesh::CreateUnmanaged<QuadUserMesh>();
		break;
	case COMBOBOX::Sphere:
		m_Mesh = UserMesh::CreateUnmanaged<SphereUserMesh>();
		break;
	case COMBOBOX::Capsule:
		m_Mesh = UserMesh::CreateUnmanaged<CapsuleUserMesh>();
		break;
	case COMBOBOX::RightTriangle:
		m_Mesh = UserMesh::CreateUnmanaged<RightTriangleUserMesh>();
		break;
	case COMBOBOX::Triangle:
		m_Mesh = UserMesh::CreateUnmanaged<TriangleUserMesh>();
		break;
	case COMBOBOX::END:
		m_Mesh = UserMesh::CreateUnmanaged<CubeUserMesh>();
		break;
	}
	m_Renderer->userMesh = m_Mesh;
	m_MeshType = comboBox;
}

void Pickable::DeleteMesh()
{
	if (m_Mesh)
	{
		m_Mesh->ReleaseUnmanaged();
		m_Mesh = nullptr;
	}
}

Pickable* Pickable::Pick()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	Vec3 HitPoint;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	for (auto pickable : g_PickableVec)
	{
		UserMeshRenderer* Renderer = pickable->GetRenderer();

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			giz->enable = true;
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
	case Type::EventObject:
		g_EventVec.push_back(this);
		break;
	case Type::Trigger:
		g_TriggerVec.push_back(this);
		break;
	}
}

int Pickable::GetTriggerVectorIndex()
{
	if(m_Type != Type::Trigger)
		return -1;

	for (int i = 0; i < g_TriggerVec.size(); ++i)
	{
		if (g_TriggerVec[i] == this)
			return i;
	}

	return -1;
}
