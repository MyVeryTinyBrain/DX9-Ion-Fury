#include "IonFuryEditorBase.h"
#include "HandlingObject.h"
#include "EditorManager.h"
#include "Gizmo.h"
#include <ItemBowAmmo.h>
#include <ItemChaingunAmmo.h>
#include <ItemLauncherAmmo.h>
#include <ItemRevolverAmmo.h>
#include <ItemShotgunAmmo.h>
#include <ItemSMGAmmo.h>
#include <ItemHealthPack.h>

std::vector<HandlingObject*> HandlingObject::g_HandlingVec;

void HandlingObject::Awake()
{
	m_PivotObject = CreateGameObject();
	g_HandlingVec.push_back(this);

	m_PivotObject->transform->parent = GetGameObject()->transform;
	m_PivotObject->transform->localPosition = Vec3(0.f, 0.f, 0.f);

	m_Renderer = m_PivotObject->AddComponent<UserMeshRenderer>();
	m_Renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	m_Renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInBlackTexture));

	SetMaterial();

	m_ChildObject = CreateGameObject();
	m_ChildObject->transform->parent = GetGameObject()->transform;
	m_ChildObject->transform->localPosition = Vec3(0.f, 0.f, 0.f);

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
}

void HandlingObject::OnDestroy()
{
	// childobj2°³ »èÁ¦?
	m_ChildObject->Destroy();
	m_PivotObject->Destroy();

	auto it = FindInContainer(g_HandlingVec, this);
	if (it != g_HandlingVec.end())
	{
		g_HandlingVec.erase(it);
		RemoveMaterial();
	}
}

void HandlingObject::SetMaterial()
{
	MaterialParameters param;
	param.renderQueue = RenderQueue::GeometryLast;
	param.zRead = false;
	param.zWrite = false;
	param.useLight = false;

	m_Material = Material::CreateUnmanaged(param);
	m_Renderer->material = m_Material;
}

void HandlingObject::RemoveMaterial()
{
	if (m_Material)
	{
		m_Material->ReleaseUnmanaged();
		m_Material = nullptr;
	}
}

Component* HandlingObject::GetHandlingComponent()
{
	//if (m_HandlingObjectType == (L"ItemBowAmmo"))
	//	return m_ChildObject->GetComponent<ItemBowAmmo>();
	//else if (m_HandlingObjectType == (L"ItemChaingunAmmo"))
	//	return static_cast<Component*>(m_ChildObject->GetComponent<ItemChaingunAmmo>());
	//else if (m_HandlingObjectType == (L"ItemLauncherAmmo"))
	//	return static_cast<Component*>(m_ChildObject->GetComponent<ItemLauncherAmmo>());
	//else if (m_HandlingObjectType == (L"ItemRevolverAmmo"))
	//	return static_cast<Component*>(m_ChildObject->GetComponent<ItemRevolverAmmo>());
	//else if (m_HandlingObjectType == (L"ItemShotgunAmmo"))
	//	return static_cast<Component*>(m_ChildObject->GetComponent<ItemShotgunAmmo>());
	//else if (m_HandlingObjectType == (L"ItemSMGAmmo"))
	//	return static_cast<Component*>(m_ChildObject->GetComponent<ItemSMGAmmo>());
	//else if (m_HandlingObjectType == (L"ItemHealthPack"))
	//	return static_cast<Component*>(m_ChildObject->GetComponent<ItemHealthPack>());
	return nullptr;
}

void HandlingObject::AddComponentToChildObject(CString Type)
{
	m_ComponentType = Type;

	if (Type == (L"ItemBowAmmo"))
		m_ChildObject->AddComponent<ItemBowAmmo>();
	else if (Type == (L"ItemChaingunAmmo"))
		m_ChildObject->AddComponent<ItemChaingunAmmo>();
	else if (Type == (L"ItemLauncherAmmo"))
		m_ChildObject->AddComponent<ItemLauncherAmmo>();
	else if (Type == (L"ItemRevolverAmmo"))
		m_ChildObject->AddComponent<ItemRevolverAmmo>();
	else if (Type == (L"ItemShotgunAmmo"))
		m_ChildObject->AddComponent<ItemShotgunAmmo>();
	else if (Type == (L"ItemSMGAmmo"))
		m_ChildObject->AddComponent<ItemSMGAmmo>();
	else if (Type == (L"ItemHealthPack"))
		m_ChildObject->AddComponent<ItemHealthPack>();
}

void HandlingObject::RemoveChildObjectAndComponent()
{
	m_ComponentType = L"";
	m_ChildObject->Destroy();
	m_ChildObject = CreateGameObject();
	m_ChildObject->transform->parent = GetGameObject()->transform;
	m_ChildObject->transform->localPosition = Vec3(0.f, 0.f, 0.f);
}

HandlingObject* HandlingObject::Pick(float& Distance)
{
	Vec3 rayPoint, rayDir;
	Vec3 HitPoint;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	Distance = 90000.f;
	HandlingObject* ClosestPicked = nullptr;

	for (auto pickable : g_HandlingVec)
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

int HandlingObject::GetHandlingVectorIndex()
{
	for (unsigned int i = 0; i < g_HandlingVec.size(); ++i)
	{
		if (g_HandlingVec[i] == this)
			return i;
	}

	return -1;
}

void HandlingObject::ClearVector()
{
	int Size = g_HandlingVec.size();
	for (int i = 0; i < Size; ++i)
	{
		g_HandlingVec[0]->GetGameObject()->Destroy();
	}

	Size = g_HandlingVec.size();
}
