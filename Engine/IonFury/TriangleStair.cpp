#include "stdafx.h"
#include "TriangleStair.h"

void TriangleStair::Awake()
{
	m_emptyRightTriangleObj = CreateGameObjectToChild(transform);

	m_backSideObj = CreateGameObjectToChild(transform);
	m_backSideObj->transform->localPosition = Vec3::back() * 0.5f;

	m_frontSideObj = CreateGameObjectToChild(transform);
	m_frontSideObj->transform->localPosition = Vec3::forawrd() * 0.5f;

	m_emptyRightTriangle = m_emptyRightTriangleObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_emptyRightTriangle);
	m_emptyRightTriangle->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleEmptySideUserMesh);

	m_backSide = m_emptyRightTriangleObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_backSide);
	m_backSide->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleBackSideUserMesh);

	m_frontSide = m_emptyRightTriangleObj->AddComponent<UserMeshRenderer>();
	m_renderers.push_back(m_frontSide);
	m_frontSide->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleFrontSideUserMesh);

	SetMaterials(Resource::FindAs<Material>(BuiltInGeometryMaterial));
}
