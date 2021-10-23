#include "shared_stdafx.h"
#include "Trigger.h"
#include "IDontDeactive.h"
#include "PhysicsLayers.h"
#include "IUsable.h"
#include "ObjectButton.h"
#include "Player.h"

void Trigger::Awake()
{
//#ifdef _DEBUG
//	m_debugRenderer = gameObject->AddComponent<UserMeshRenderer>();
//	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
//	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
//	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
//#endif

	// 버튼 테스트
	//auto button = gameObject->AddComponent<ObjectButton>();
	//AddSubordinationComponent(button);
}

void Trigger::Update()
{
	if (m_used && m_once)
	{
		return;
	}

	if (m_method == TriggerMethod::Touch)
	{
		Collider* collider = Physics::OverlapBox(
			transform->scale,
			transform->position,
			transform->rotation,
			1 << (uint8_t)PhysicsLayers::Player,
			PhysicsQueryType::Collider);

		if (collider)
		{
			Use();
		}
	}
}

void Trigger::SetTriggerOnce(bool value)
{
	m_once = value;
}

void Trigger::SetMethod(TriggerMethod value)
{
	if (value == m_method)
	{
		return;
	}

	m_method = value;

	if (value == TriggerMethod::Button || value == TriggerMethod::CardCheck)
	{
		if (!m_body)
		{
			m_body = gameObject->AddComponent<Rigidbody>();
		}

		if (!m_trigger)
		{
			m_trigger = gameObject->AddComponent<BoxCollider>();
		}

		if (m_body)
		{
			m_body->enable = true;

			m_body->isKinematic = true;
		}

		if (m_trigger)
		{
			m_trigger->enable = true;

			m_trigger->isTrigger = true;
			m_trigger->layerIndex = (uint8_t)PhysicsLayers::InputTrigger;
		}
	}
	else
	{
		if (m_body)
		{
			m_body->enable = false;
		}
		if (m_trigger)
		{
			m_trigger->enable = false;
		}
	}
}

void Trigger::AddSubordinationComponent(Component* value)
{
	IDontDeactive* includedInterface = dynamic_cast<IDontDeactive*>(value);

	if (!includedInterface && value)
	{
		value->gameObject->activeSelf = false;
	}

	m_connected.push_back(value);
}

void Trigger::ActiveAllGameObjects()
{
	for (auto& comp : m_connected)
	{
		if (comp.IsNull())
		{
			continue;
		}

		comp->gameObject->activeSelf = true;
	}
}

void Trigger::Use()
{
	bool valid = true;

	switch (m_method)
	{
		case TriggerMethod::CardCheck:
			{
				valid = Player::GetInstance()->cardKey;
				Player::GetInstance()->cardKey = false;
			}
			break;
	}

	if (valid)
	{
		m_used = true;

		ActiveAllGameObjects();

		OnTrigger();
	}

	for (auto& comp : m_connected)
	{
		if (comp.IsNull())
		{
			continue;
		}

		IUsable* usable = dynamic_cast<IUsable*>(comp.GetPointer());
		if (usable)
		{
			usable->OnUse(valid);
		}
	}
}

const std::vector<Ref<Component>>& Trigger::GetConnections() const
{
	return m_connected;
}

TriggerMethod Trigger::GetMethod() const
{
	return m_method;
}
