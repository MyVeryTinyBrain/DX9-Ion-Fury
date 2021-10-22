#include "shared_stdafx.h"
#include "ObjectButton.h"
#include "Cube.h"

void ObjectButton::Awake()
{
	m_nonPressTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/button/button0.png");
	m_pressTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/button/button1.png");
	m_sideTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/button/button2.png");

	m_root = CreateGameObjectToChild(transform);
	m_root->transform->localScale = Vec3(1.0f, 1.0f, 0.1f);

	m_cube = m_root->AddComponent<Cube>();

	m_cube->forward->SetTexture(0, m_nonPressTexture);

	m_cube->back->SetTexture(0, m_sideTexture);
	m_cube->left->SetTexture(0, m_sideTexture);
	m_cube->right->SetTexture(0, m_sideTexture);
	m_cube->top->SetTexture(0, m_sideTexture);
	m_cube->bottom->SetTexture(0, m_sideTexture);
}

void ObjectButton::Update()
{
	auto ref = m_cube->forward->GetTexture(0);
	Texture* tex = ref.GetPointer();

	if (tex == m_pressTexture)
	{
		if (m_pressingAccumulate > 0.3f)
		{
			m_pressingAccumulate = 0;
			m_cube->forward->SetTexture(0, m_nonPressTexture);
		}

		m_pressingAccumulate += Time::DeltaTime();
	}
}

void ObjectButton::OnUse(bool valid)
{
	m_cube->forward->SetTexture(0, m_pressTexture);
}
