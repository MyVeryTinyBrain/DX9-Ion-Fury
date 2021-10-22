#include "shared_stdafx.h"
#include "ObjectAutoDoor.h"
#include "Player.h"
#include "SoundMgr.h"

void ObjectAutoDoor::Awake()
{
	//{
	//	auto debugRendererObj = CreateGameObjectToChild(transform);
	//	auto renderer = debugRendererObj->AddComponent<UserMeshRenderer>();
	//	renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//}

	m_root = CreateGameObjectToChild(transform);

	m_leftFrameObj = CreateGameObjectToChild(m_root->transform);
	m_leftFrameObj->transform->localScale = Vec3(0.1f, 1.0f, 0.1f);
	m_leftFrameObj->transform->localPosition = Vec3(-0.45f, 0, 0);
	{
		auto renderer = m_leftFrameObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/door/frame.png"));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}

	m_rightFrameObj = CreateGameObjectToChild(m_root->transform);
	m_rightFrameObj->transform->localScale = Vec3(0.1f, 1.0f, 0.1f);
	m_rightFrameObj->transform->localPosition = Vec3(0.45f, 0, 0);
	{
		auto renderer = m_rightFrameObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/door/frame.png"));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}

	m_topFrameObj = CreateGameObjectToChild(m_root->transform);
	m_topFrameObj->transform->localScale = Vec3(0.8f, 0.1f, 0.1f);
	m_topFrameObj->transform->localPosition = Vec3(0, 0.45f, 0);
	{
		auto renderer = m_topFrameObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/door/frame.png"));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}

	m_bottomFrameObj = CreateGameObjectToChild(m_root->transform);
	m_bottomFrameObj->transform->localScale = Vec3(0.8f, 0.02f, 0.1f);
	m_bottomFrameObj->transform->localPosition = Vec3(0, -0.49f, 0);
	{
		auto renderer = m_bottomFrameObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/door/frame.png"));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}

	m_doorObj = CreateGameObjectToChild(m_root->transform);
	m_doorObj->transform->localScale = Vec3(1, 1, 0.05f);
	{
		auto renderer = m_doorObj->AddComponent<UserMeshRenderer>();
		renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/door/door.png"));
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	}
	{
		auto body = m_doorObj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = m_doorObj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}
}

void ObjectAutoDoor::Update()
{
	if (Time::TimeScale() == 0)
	{
		return;
	}

	if (m_autoOpen)
	{
		Vec3 player = Player::GetInstance()->transform->position;
		Vec3 pos = transform->position;

		Vec2 player2d = Vec2(player.x, player.z);
		Vec2 pos2d = Vec2(pos.x, pos.z);

		float maxAxis = Abs(transform->scale.y);
		if (maxAxis < Abs(transform->scale.x))
			maxAxis = Abs(transform->scale.x);

		float distance = Vec3::Distance(player, pos);

		if (distance <= maxAxis)
		{
			Open();
		}
		else
		{
			Close();
		}
	}

	m_doorObj->transform->localPosition =
		Vec3::Lerp(m_doorObj->transform->localPosition, m_targetLocalPosition, Time::DeltaTime() * 5.0f);
}

void ObjectAutoDoor::OnUse(bool valid)
{
	if (valid)
	{
		SetAutoOpen(false);
		Open();
	}
}

void ObjectAutoDoor::Toggle()
{
	if (!m_state)
	{
		m_state = true;
		Open();
	}
	else
	{
		m_state = false;
		Close();
	}
}

void ObjectAutoDoor::Open()
{
	if (m_state)
	{
		return;
	}

	m_targetLocalPosition = Vec3(0, 0.8f, 0);
	m_state = true;

	SoundMgr::Play(L"../SharedResource/Sound/door/door_scifi02_open.ogg", CHANNELID::OBJECT_INPUT);
}

void ObjectAutoDoor::Close()
{
	if (!m_state)
	{
		return;
	}

	m_targetLocalPosition = Vec3(0, 0, 0);
	m_state = false;

	SoundMgr::Play(L"../SharedResource/Sound/door/door_scifi02_close.ogg", CHANNELID::OBJECT_INPUT);
}

void ObjectAutoDoor::SetAutoOpen(bool value)
{
	m_autoOpen = value;
}
