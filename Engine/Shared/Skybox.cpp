#include "shared_stdafx.h"
#include "Skybox.h"
#include "Cube.h"
#include "RenderLayers.h"

void Skybox::Awake()
{
	auto cubeObj = CreateGameObjectToChild(transform);
	m_cube = cubeObj->AddComponent<Cube>();
	m_cube->SetMaterials(Resource::FindAs<Material>(BuiltInSkyboxBackgroundMaterial));
	m_cube->SetRenderLayers((int)RenderLayers::Generic);

	m_cube->left->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/skybox/left.png"));
	m_cube->right->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/skybox/right.png"));
	m_cube->top->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/skybox/top.png"));
	m_cube->bottom->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/skybox/bottom.png"));
	m_cube->forward->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/skybox/forward.png"));
	m_cube->back->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/skybox/back.png"));
}

void Skybox::BeginRender()
{
	Camera* mainCamera = Camera::GetMainCamera();

	if (!mainCamera)
	{
		return;
	}

	transform->position = mainCamera->transform->position;
	transform->scale = Vec3::one() * 5.0f;
}

void Skybox::SetLeftTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->left->SetTexture(0, tex);
}

void Skybox::SetRightTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->right->SetTexture(0, tex);
}

void Skybox::SetTopTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->top->SetTexture(0, tex);
}

void Skybox::SetBottomTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->bottom->SetTexture(0, tex);
}

void Skybox::SetForwardTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->forward->SetTexture(0, tex);
}

void Skybox::SetBackTexture(const wstring& localPath)
{
	Texture* tex = Resource::FindAs<Texture>(localPath);
	m_cube->back->SetTexture(0, tex);
}
