#include "IonFuryEditorBase.h"
#include "LightObject.h"
#include "LightManager.h"
#include "EditorManager.h"
#include "Gizmo.h"

void LightObject::Awake()
{
	m_LightChildObject->transform->parent = GetGameObject()->transform;
	m_LightChildObject->transform->localPosition = Vec3::zero();

}

void LightObject::Update()
{

}

void LightObject::OnDestroy()
{
}

void LightObject::LightSettings(const wstring& localPathMesh)
{
	m_LightRenderer = m_LightChildObject->AddComponent<UserMeshRenderer>();
	m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(localPathMesh);
}

