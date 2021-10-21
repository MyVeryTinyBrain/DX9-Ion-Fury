#include "shared_stdafx.h"
#include "Trigger.h"
#include "IDontDeactive.h"
#include "PhysicsLayers.h"
#include "IUsable.h"
#include "ObjectButton.h"

void Trigger::Awake()
{
#ifdef _DEBUG
	m_debugRenderer = gameObject->AddComponent<UserMeshRenderer>();
	m_debugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	m_debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	m_debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
#endif

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

	if (m_method == Method::Touch)
	{
		Collider* collider = Physics::OverlapBox(
			transform->position,
			transform->scale,
			transform->rotation,
			1 << (uint8_t)PhysicsLayers::Player,
			PhysicsQueryType::Collider);

		if (collider)
		{
			ActiveAllGameObjects();
			Use();
			OnTrigger();
			m_used = true;
		}
	}
}

void Trigger::SetTriggerOnce(bool value)
{
	m_once = value;
}

void Trigger::SetMethod(Method value)
{
	if (value == m_method)
	{
		return;
	}

	m_method = value;

	if (value == Method::Button)
	{
		if (!m_body)
		{
			m_body = gameObject->AddComponent<Rigidbody>();
			m_body->isKinematic = true;
		}

		if (!m_trigger)
		{
			m_trigger = gameObject->AddComponent<BoxCollider>();
			m_trigger->isTrigger = true;
			m_trigger->layerIndex = (uint8_t)PhysicsLayers::InputTrigger;
		}

		if (m_body)
		{
			m_body->enable = true;
		}

		if (m_trigger)
		{
			m_trigger->enable = true;
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

	// 사용시 주석 해제
	//if (!includedInterface && value)
	//{
	//	value->gameObject->activeSelf = false;
	//}

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
	for (auto& comp : m_connected)
	{
		if (comp.IsNull())
		{
			continue;
		}

		IUsable* usable = dynamic_cast<IUsable*>(comp.GetPointer());
		if (usable)
		{
			usable->OnUse();
		}
	}
}

const std::vector<Ref<Component>>& Trigger::GetConnections() const
{
	return m_connected;
}
