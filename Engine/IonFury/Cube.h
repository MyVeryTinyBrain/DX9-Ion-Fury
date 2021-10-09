#pragma once

#include "UserMixMesh.h"

class Cube : public UserMixMesh
{
	OverrideComponentFunction(Awake);

private:

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

