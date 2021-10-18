#pragma once

#include "UserMixMesh.h"

class Cube : public UserMixMesh
{
	OverrideComponentFunction(Awake);

public:

	UserMeshRenderer* GetLeftRenderer() const;

	UserMeshRenderer* GetRightRenderer() const;

	UserMeshRenderer* GetTopRenderer() const;

	UserMeshRenderer* GetBottomRenderer() const;

	UserMeshRenderer* GetForwardRenderer() const;

	UserMeshRenderer* GetBackRenderer() const;

	__declspec(property(get = GetLeftRenderer)) UserMeshRenderer* left;

	__declspec(property(get = GetRightRenderer)) UserMeshRenderer* right;

	__declspec(property(get = GetTopRenderer)) UserMeshRenderer* top;

	__declspec(property(get = GetBottomRenderer)) UserMeshRenderer* bottom;

	__declspec(property(get = GetForwardRenderer)) UserMeshRenderer* forward;

	__declspec(property(get = GetBackRenderer)) UserMeshRenderer* back;

protected:

	GameObject*			m_leftObj			= nullptr;

	GameObject*			m_rightObj			= nullptr;

	GameObject*			m_topObj			= nullptr;

	GameObject*			m_bottomObj			= nullptr;

	GameObject*			m_forwardObj		= nullptr;

	GameObject*			m_backObj			= nullptr;

	UserMeshRenderer*	m_left				= nullptr;
	
	UserMeshRenderer*	m_right				= nullptr;
	
	UserMeshRenderer*	m_top				= nullptr;
	
	UserMeshRenderer*	m_bottom			= nullptr;
	
	UserMeshRenderer*	m_forward			= nullptr;
	
	UserMeshRenderer*	m_back				= nullptr;
};

