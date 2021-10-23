#include "shared_stdafx.h"
#include "ObjectCarBlack.h"
#include "Cube.h"

void ObjectCarBlack::Awake()
{
	m_cube = gameObject->AddComponent<Cube>();

	m_cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/black/front.png"));
	m_cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/black/back.png"));
	m_cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/black/side.png"));
	m_cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/black/side.png"));
	m_cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/black/top.png"));
	m_cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/car/black/top.png"));

	{
		auto colliderObj = CreateGameObjectToChild(transform);
		auto body = colliderObj->AddComponent<Rigidbody>();
		auto collider = colliderObj->AddComponent<BoxCollider>();
		body->isKinematic = true;
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}
}