#include "shared_stdafx.h"
#include "ObjectCarBlue.h"
#include "Cube.h"

void ObjectCarBlue::Awake()
{
	m_cube = gameObject->AddComponent<Cube>();

	m_cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/blue/front.png"));
	m_cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/blue/back.png"));
	m_cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/blue/side.png"));
	m_cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/blue/side.png"));
	m_cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/blue/top.png"));
	m_cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/blue/top.png"));
}