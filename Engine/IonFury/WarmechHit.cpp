#include "stdafx.h"
#include "WarmechHit.h"

void WarmechHit::Awake()
{
	m_moveSpeed = 3.0f;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localScale = Vec3::one() * 0.25f;


	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();

	//{	// For debug
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	m_debugRenderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}
}

void WarmechHit::Update()
{
}

void WarmechHit::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
