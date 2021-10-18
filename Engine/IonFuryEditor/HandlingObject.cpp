#include "IonFuryEditorBase.h"
#include "HandlingObject.h"
#include "EditorManager.h"
#include "Gizmo.h"
#include "../IonFury/ItemBowAmmo.h"
#include "../IonFury/ItemChaingunAmmo.h"
#include "../IonFury/ItemLauncherAmmo.h"
#include "../IonFury/ItemRevolverAmmo.h"
#include "../IonFury/ItemShotgunAmmo.h"
#include "../IonFury/ItemSMGAmmo.h"
#include "../IonFury/ItemHealthPack.h"

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
