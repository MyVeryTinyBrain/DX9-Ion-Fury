#include "shared_stdafx.h"
#include "OrthoEffect.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"
#include "SpriteAnimation.h"

void OrthoEffect::Awake()
{
	SpriteAnimator::Awake();

	m_renderer = gameObject->AddComponent<UserMeshRenderer>();
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_renderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_renderer->overlayRenderOrder = (int)OverlayRenderOrders::OrthoBackEffect0;
	m_renderer->renderLayerIndex = (uint8_t)RenderLayers::Overlay;

	InitializeAnimation(&m_animation);

	if (m_animation)
	{
		SetDefaultAnimation(m_animation);
	}
}

void OrthoEffect::Start()
{
	SpriteAnimator::Start();

	if (!m_animation)
	{
		gameObject->Destroy();
		return;
	}
}

void OrthoEffect::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (m_requireDestroy)
	{
		gameObject->Destroy();
		return;
	}
}

void OrthoEffect::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_animation);
}

void OrthoEffect::OnAnimationEnd(const SpriteAnimation* current)
{
	m_requireDestroy = true;
}

void OrthoEffect::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void OrthoEffect::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void OrthoEffect::SetOverlayRenderOrder(int value)
{
	m_renderer->overlayRenderOrder = value;
}

void OrthoEffect::AddTexture(const wstring& textureLocalPath)
{
	Ref<Texture> ref = Resource::FindAs<Texture>(textureLocalPath);

	if (ref.IsNull())
	{
		return;
	}

	if (!m_animation)
	{
		m_animation = new SpriteAnimation;
		m_renderer->SetTexture(0, ref);
		SetDefaultAnimation(m_animation);
	}

	m_animation->AddTexture(textureLocalPath);
}

void OrthoEffect::SetInterval(float value)
{
	if (m_animation)
	{
		m_animation->interval = value;
	}
}
