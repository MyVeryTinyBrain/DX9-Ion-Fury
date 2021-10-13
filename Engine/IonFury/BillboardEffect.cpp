#include "stdafx.h"
#include "BillboardEffect.h"
#include "RenderLayers.h"
#include "SpriteAnimation.h"

void BillboardEffect::Awake()
{
	SpriteAnimator::Awake();

	m_renderer = gameObject->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);

	SetToAlphaTest();

	InitializeAnimation(&m_animation);

	if (m_animation)
	{
		SetDefaultAnimation(m_animation);
	}
}

void BillboardEffect::Start()
{
	SpriteAnimator::Start();

	if (!m_animation)
	{
		gameObject->Destroy();
		return;
	}
}

void BillboardEffect::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (m_requireDestroy)
	{
		gameObject->Destroy();
		return;
	}
}

void BillboardEffect::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_animation);
}

void BillboardEffect::OnAnimationEnd(const SpriteAnimation* current)
{
	m_requireDestroy = true;
}

void BillboardEffect::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void BillboardEffect::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void BillboardEffect::AddTexture(const wstring& textureLocalPath)
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

void BillboardEffect::SetToAlphaTest()
{
	m_renderer->material = Resource::FindAs<Material>(BuiltInNolightAlphaTestMaterial);
}

void BillboardEffect::SetToTransparent()
{
	m_renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
}

void BillboardEffect::SetInterval(float value)
{
	if (m_animation)
	{
		m_animation->interval = value;
	}
}
