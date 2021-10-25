#include "shared_stdafx.h"
#include "ObjectCardScreen.h"
#include "Cube.h"
#include "SoundMgr.h"

void ObjectCardScreen::Awake()
{
	m_defaultTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/cardscreen/screen_green.png");
	m_deniedTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/cardscreen/screen_red.png");
	m_acceptTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/cardscreen/screen_blue.png");
	m_sideTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/cardscreen/side.png");

	m_root = CreateGameObjectToChild(transform);
	m_root->transform->localScale = Vec3(1.0f, 1.0f, 0.1f);

	m_cube = m_root->AddComponent<Cube>();

	m_cube->forward->SetTexture(0, m_defaultTexture);

	m_cube->back->SetTexture(0, m_sideTexture);
	m_cube->left->SetTexture(0, m_sideTexture);
	m_cube->right->SetTexture(0, m_sideTexture);
	m_cube->top->SetTexture(0, m_sideTexture);
	m_cube->bottom->SetTexture(0, m_sideTexture);
}

void ObjectCardScreen::Update()
{
	auto ref = m_cube->forward->GetTexture(0);
	Texture* tex = ref.GetPointer();

	if (tex != m_defaultTexture)
	{
		if (m_changeAccumulate > 0.3f)
		{
			m_changeAccumulate = 0;
			m_cube->forward->SetTexture(0, m_defaultTexture);
		}

		m_changeAccumulate += Time::DeltaTime();
	}
}

void ObjectCardScreen::OnUse(bool valid)
{
	if (valid)
	{
		m_cube->forward->SetTexture(0, m_acceptTexture);

		SoundMgr::Play(L"../SharedResource/Sound/input/keycard_unlock.ogg", CHANNELID::OBJECT_INPUT);
	}
	else
	{
		m_cube->forward->SetTexture(0, m_deniedTexture);

		SoundMgr::Play(L"../SharedResource/Sound/input/keycard_locked.ogg", CHANNELID::OBJECT_INPUT);
	}
}

void ObjectCardScreen::OnDisable()
{
}
