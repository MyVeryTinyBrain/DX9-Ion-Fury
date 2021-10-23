#include "shared_stdafx.h"
#include "ObjectCarRed.h"
#include "Cube.h"

void ObjectCarRed::Awake()
{
	m_cube = gameObject->AddComponent<Cube>();

	m_cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/red/front.png"));
	m_cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/red/back.png"));
	m_cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/red/side.png"));
	m_cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/red/side.png"));
	m_cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/red/top.png"));
	m_cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/red/top.png"));
}
