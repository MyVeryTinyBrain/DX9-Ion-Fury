#pragma once

#include "UserMixMesh.h"

class TriangleStair : public UserMixMesh
{
	OverrideComponentFunction(Awake);

public:

	UserMeshRenderer* GetEmptyRightTriangle() const;

	UserMeshRenderer* GetBackSide() const;

	UserMeshRenderer* GetFrontSide() const;

	__declspec(property(get = GetEmptyRightTriangle)) UserMeshRenderer* emptyRightTriangle;

	__declspec(property(get = GetBackSide)) UserMeshRenderer* backSide;

	__declspec(property(get = GetFrontSide)) UserMeshRenderer* frontSide;

private:

	GameObject*			m_emptyRightTriangleObj		= nullptr;

	GameObject*			m_backSideObj				= nullptr;

	GameObject*			m_frontSideObj				= nullptr;

	UserMeshRenderer*	m_emptyRightTriangle		= nullptr;

	UserMeshRenderer*	m_backSide					= nullptr;

	UserMeshRenderer*	m_frontSide					= nullptr;
};

