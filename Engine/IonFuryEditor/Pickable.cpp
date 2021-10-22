#include "IonFuryEditorBase.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorManager.h"
#include "EditorEnum.h"
#include "HandlingObject.h"

#include <BasicMutant.h>
#include <Mutant.h>
#include <CultistArcher.h>
#include <CultistGunner.h>
#include <Deacon.h>
#include <Drone.h>
#include <Liberator.h>
#include <Spider.h>
#include <Skull.h>
#include <Warmech.h>
#include <Wendigo.h>

#include <ObjectAutoDoor.h>
#include <ObjectManualDoor.h>
#include <ObjectCardScreen.h>
#include <ObjectButton.h>


std::vector<Pickable*> Pickable::g_PickableVec;

std::vector<Pickable*> Pickable::g_MapVec;
std::vector<Pickable*> Pickable::g_TriggerVec;
//std::vector<Pickable*> Pickable::g_EventVec;

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
	m_ChildObject->transform->position = this->transform->position;
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
	case Type::Trigger:
		ClearEventVector();

		it = FindInContainer(g_TriggerVec, this);
		if (it != g_TriggerVec.end())
			g_TriggerVec.erase(it);
		break;
	}

	DeleteMesh();
	DeleteMaterial();

	m_ChildObject->Destroy(); //이게 맞나..?
	if (m_ComponentObject)
		m_ComponentObject->Destroy();
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

Pickable* Pickable::Pick(float& Distance)
{
	Vec3 rayPoint, rayDir;
	Vec3 HitPoint;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	Distance = 90000.f;
	Pickable* ClosestPicked = nullptr;

	for (auto pickable : g_PickableVec)
	{
		UserMeshRenderer* Renderer = pickable->GetRenderer();
		Input::GetMouseWorldRay(rayPoint, rayDir);

		if (Renderer->Raycast(HitPoint, rayPoint, rayDir))
		{
			giz->enable = true;
			
			Vec3 Between = rayPoint - HitPoint;
			float BetweenDistance = sqrtf((Between.x * Between.x) + (Between.y * Between.y) + (Between.z * Between.z));
			if (Distance >= BetweenDistance)
			{
				EditorManager::GetInstance()->GetGizmo()->Attach(pickable->GetGameObject()->transform);
				Distance = BetweenDistance;
				ClosestPicked = pickable;
			}
		}
	}

	return ClosestPicked;
}

void Pickable::PushInVector(Type type)
{
	m_Type = type;
	switch (m_Type)
	{
	case Type::Map:
		g_MapVec.push_back(this);
		break;
	case Type::Trigger:
		g_TriggerVec.push_back(this);
		break;
	}
}

void Pickable::PushInEventVector(Pickable* Event)
{
	Event->SetType(Type::EventObject);
	m_EventVec.push_back(Event);
}

void Pickable::SetNoLightTransparentMaterial()
{
	m_Renderer->SetMaterial(Resource::FindAs<Material>(BuiltInNolightTransparentMaterial));
}

void Pickable::DeleteMaterial()
{
	if (m_Material)
	{
		m_Material->ReleaseUnmanaged();
		m_Material = nullptr;
	}
}

void Pickable::RemoveFamilyTransFromChildObj()
{
	m_ChildObject->transform->parent = nullptr;
}

int Pickable::GetTriggerVectorIndex()
{
	if(m_Type != Type::Trigger)
		return -1;

	for (unsigned int i = 0; i < g_TriggerVec.size(); ++i)
	{
		if (g_TriggerVec[i] == this)
			return i;
	}

	return -1;
}

void Pickable::GetEventVectorIndex(int& TriggerIndex, int& EventIndex)
{
	if (m_Type != Type::EventObject)
	{
		TriggerIndex = -1;
		EventIndex = -1;
		return;
	}

	for (unsigned int i = 0; i < g_TriggerVec.size(); ++i)
	{
		std::vector<Pickable*> EventVec = g_TriggerVec[i]->GetEventVec();
		for (unsigned int j = 0; j < EventVec.size(); ++j)
			if (EventVec[j] == this)
			{
				TriggerIndex = i;
				EventIndex = j;
				return;
			}
	}

	TriggerIndex = -1;
	EventIndex = -1;
	return;
}

void Pickable::ClearEventVector()
{
	int Size = m_EventVec.size();
	for (int i = 0; i < Size; ++i)
	{
		m_EventVec[0]->Destroy();
		m_EventVec.erase(m_EventVec.begin());
	}

	Size = m_EventVec.size();
}

void Pickable::ClearTriggerVector()
{
	int Size = g_TriggerVec.size();
	for (int i = 0; i < Size; ++i)
	{
		g_TriggerVec[0]->Destroy();
	}
}

void Pickable::ClearMapVector()
{
	int Size = g_MapVec.size();
	for (int i = 0; i < Size; ++i)
	{
		g_MapVec[0]->Destroy();
	}
}

void Pickable::RemoveEventObject(int idx)
{
	m_EventVec[idx]->Destroy();
	m_EventVec.erase(m_EventVec.begin() + idx);
}

void Pickable::SetComponentToPickable(EventType type)
{
	m_EventType = type;

	switch (m_EventType)
	{
	case EventType::BasicMutant:
		m_ComponentObject->AddComponent<BasicMutant>();
		break;
	case EventType::Mutant:
		m_ComponentObject->AddComponent<Mutant>();
		break;
	case EventType::CultistArcher:
		m_ComponentObject->AddComponent<CultistArcher>();
		break;
	case EventType::CultistGunner:
		m_ComponentObject->AddComponent<CultistGunner>();
		break;
	case EventType::Deacon:
		m_ComponentObject->AddComponent<Deacon>();
		break;
	case EventType::Drone:
		m_ComponentObject->AddComponent<Drone>();
		break;
	case EventType::Liberator:
		m_ComponentObject->AddComponent<Liberator>();
		break;
	case EventType::Spider:
		m_ComponentObject->AddComponent<Spider>();
		break;
	case EventType::Skull:
		m_ComponentObject->AddComponent<Skull>();
		break;
	case EventType::Warmech:
		m_ComponentObject->AddComponent<Warmech>();
		break;
	case EventType::Wendigo:
		m_ComponentObject->AddComponent<Wendigo>();
		break;

	case EventType::ObjectAutoDoor:
		m_ComponentObject->AddComponent<ObjectAutoDoor>();
		break;
	case EventType::ObjectManualDoor:
		m_ComponentObject->AddComponent<ObjectManualDoor>();
		break;
	case EventType::ObjectCardScreen:
		m_ComponentObject->AddComponent<ObjectCardScreen>();
		break;
	case EventType::ObjectButton:
		m_ComponentObject->AddComponent<ObjectButton>();
		break;
	}
}

void Pickable::RemoveCompObjectAndComponent()
{
	m_EventType = EventType::EventObjectEnd;
	m_ComponentObject->Destroy();
	CreateComponentObject();
}

void Pickable::CreateComponentObject()
{
	m_ComponentObject = CreateGameObject();
	m_ComponentObject->transform->parent = GetGameObject()->transform;
	m_ComponentObject->transform->localPosition = Vec3(0.f, 0.f, 0.f);
}

void Pickable::SetOverSeeBlackMaterial()
{
	MaterialParameters param;
	param.renderQueue = RenderQueue::GeometryLast;
	param.zRead = false;
	param.zWrite = false;
	param.useLight = false;

	m_Material = Material::CreateUnmanaged(param);
	m_Renderer->material = m_Material;//////////////////////
}
