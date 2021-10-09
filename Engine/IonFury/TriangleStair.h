#pragma once

#include "UserMixMesh.h"

class TriangleStair : public UserMixMesh
{
	OverrideComponentFunction(Awake);

private:

	GameObject*			m_emptyRightTriangleObj		= nullptr;

	GameObject*			m_backSideObj				= nullptr;

	GameObject*			m_frontSideObj				= nullptr;

	UserMeshRenderer*	m_emptyRightTriangle		= nullptr;

	UserMeshRenderer*	m_backSide					= nullptr;

	UserMeshRenderer*	m_frontSide					= nullptr;
};

