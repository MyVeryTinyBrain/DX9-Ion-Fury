#include "stdafx.h"
#include "Cube.h"

void Cube::Awake()
{
	m_leftObj = CreateGameObjectToChild(transform);
	m_leftObj->transform->localPosition = Vec3::left() * 0.5f;
	m_leftObj->transform->localEulerAngle = Vec3(0, 180, 0);

	m_rightObj = CreateGameObjectToChild(transform);
	m_rightObj->transform->localPosition = Vec3::right() * 0.5f;
	m_rightObj->transform->localEulerAngle = Vec3(0, 0, 0);

	m_topObj = CreateGameObjectToChild(transform);
	m_topObj->transform->localPosition = Vec3::up() * 0.5f;
	m_topObj->transform->localEulerAngle = Vec3(0, 0, 0);

	m_bottomObj = CreateGameObjectToChild(transform);
	m_bottomObj->transform->localPosition = Vec3::down() * 0.5f;
	m_bottomObj->transform->localEulerAngle = Vec3(0, 0, 180);

	m_forwardObj = CreateGameObjectToChild(transform);
	m_forwardObj->transform->localPosition = Vec3::forawrd() * 0.5f;
	m_forwardObj->transform->localEulerAngle = Vec3(0, 180, 0);

	m_backObj = CreateGameObjectToChild(transform);
	m_backObj->transform->localPosition = Vec3::back() * 0.5f;
	m_backObj->transform->localEulerAngle = Vec3(0, 0, 0);

	m_left = m_leftObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_left);
	m_left->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadRightUserMesh);

	m_right = m_rightObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_right);
	m_right->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadRightUserMesh);

	m_top = m_topObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_top);
	m_top->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadTopUserMesh);

	m_bottom = m_bottomObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_bottom);
	m_bottom->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadTopUserMesh);

	m_forward = m_forwardObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_forward);
	m_forward->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadForwardUserMesh);

	m_back = m_backObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_back);
	m_back->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadForwardUserMesh);

	SetMaterials(Resource::FindAs<Material>(BuiltInGeometryMaterial));
}

UserMeshRenderer* Cube::GetLeftRenderer() const
{
	return m_left;
}

UserMeshRenderer* Cube::GetRightRenderer() const
{
	return m_right;
}

UserMeshRenderer* Cube::GetTopRenderer() const
{
	return m_top;
}

UserMeshRenderer* Cube::GetBottomRenderer() const
{
	return m_bottom;
}

UserMeshRenderer* Cube::GetForwardRenderer() const
{
	return m_forward;
}

UserMeshRenderer* Cube::GetBackRenderer() const
{
	return m_back;
}
