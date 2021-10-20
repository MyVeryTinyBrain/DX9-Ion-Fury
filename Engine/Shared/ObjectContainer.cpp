#include "shared_stdafx.h"
#include "ObjectContainer.h"
#include "Cube.h"
#include "RenderLayers.h"

void ObjectContainer::Awake()
{
	{
		auto colliderObj = CreateGameObjectToChild(transform);
		colliderObj->transform->localEulerAngle = Vec3(0, 0, 0);
		auto body = colliderObj->AddComponent<Rigidbody>();
		auto collider = colliderObj->AddComponent<RightTriangleCollider>();
		body->isKinematic = true;
		collider->friction = 1.0f;
		collider->restitution = 1.0f;

	}

	{
		auto obj = CreateGameObjectToChild(transform);
		m_cube = obj->AddComponent<Cube>();

		//m_cube->SetMaterials(Resource::FindAs<Material>(BuiltInPriorityMaterial));
		//m_cube->SetRenderLayers((int)RenderLayers::Generic);
		
	}
}

void ObjectContainer::BeginRender()
{
	Camera* mainCamera = Camera::GetMainCamera();

	if (!mainCamera)
	{
		return;
	}

	//transform->position = mainCamera->transform->position;
	//transform->scale = Vec3::one() * 5.0f;
}

void ObjectContainer::SetLeftTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->left->SetTexture(0, tex);
}

void ObjectContainer::SetRightTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->right->SetTexture(0, tex);
}

void ObjectContainer::SetTopTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->top->SetTexture(0, tex);
}

void ObjectContainer::SetBottomTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->bottom->SetTexture(0, tex);
}

void ObjectContainer::SetForwardTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->forward->SetTexture(0, tex);
}

void ObjectContainer::SetBackTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->back->SetTexture(0, tex);
}
