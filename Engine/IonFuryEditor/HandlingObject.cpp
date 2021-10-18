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
	m_ChildObject = CreateGameObject();
	g_HandlingVec.push_back(this);

	m_ChildObject->transform->parent = GetGameObject()->transform;
	m_ChildObject->transform->localPosition = Vec3(0.f, 0.f, 0.f);

	m_Renderer = m_ChildObject->AddComponent<UserMeshRenderer>();
	m_Renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	m_Renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInBlackTexture));

	SetMaterial();

	EditorManager::GetInstance()->GetGizmo()->Attach(transform);
}

void HandlingObject::OnDestroy()
{
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

void HandlingObject::AddTypeToChildObject(CString Type)
{
	if (Type == (L"ItemSMGAmmo"))
		m_ChildObject->AddComponent<ItemSMGAmmo>();
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
