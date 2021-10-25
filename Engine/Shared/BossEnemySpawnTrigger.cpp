#include "shared_stdafx.h"
#include "BossEnemySpawnTrigger.h"
#include "IMonsterSpawn.h"

#include <random>
#include <functional>

std::vector<BossEnemySpawnTrigger*> BossEnemySpawnTrigger::g_triggers;

void BossEnemySpawnTrigger::Awake()
{
	Trigger::Awake();

	g_triggers.push_back(this);

	m_spawnTimer = m_spawnDelay + float(rand() % 15);
}

void BossEnemySpawnTrigger::Update()
{
	Trigger::Update();

	if (m_connected.size() == 0)
	{
		enable = false;
		return;
	}

	if (m_spawnTimer <= 0)
	{
		m_spawnTimer = m_spawnDelay + float(rand() % 15);

		Component* comp = m_connected.front().GetPointer();

		if (comp)
		{
			IMonsterSpawn* onSpawn = dynamic_cast<IMonsterSpawn*>(comp);
			if (onSpawn)
			{
				onSpawn->OnSpawn();
			}

			comp->gameObject->activeSelf = true;
		}

		m_connected.erase(m_connected.begin());
	}
	else
	{
		m_spawnTimer -= Time::DeltaTime();
	}
}

void BossEnemySpawnTrigger::OnDestroy()
{
	Trigger::OnDestroy();

	auto find_it = FindInContainer(g_triggers, this);

	if (find_it != g_triggers.end())
	{
		g_triggers.erase(find_it);
	}
}

void BossEnemySpawnTrigger::EnableAll()
{
	for (auto& trigger : g_triggers)
	{
		trigger->enable = true;
	}
}

void BossEnemySpawnTrigger::DisableAll()
{
	for (auto& trigger : g_triggers)
	{
		trigger->enable = false;
	}
}

Vec3 BossEnemySpawnTrigger::GetRandomPointInBox() const
{
	std::random_device rd;
	std::mt19937 engine(rd());

	float x, y, z;

	{
		std::uniform_real_distribution<float> distribution(-0.5f, 0.5f);
		x = distribution(engine);
	}

	{
		std::uniform_real_distribution<float> distribution(-0.5f, 0.5f);
		y = distribution(engine);
	}

	{
		std::uniform_real_distribution<float> distribution(-0.5f, 0.5f);
		z = distribution(engine);
	}

	Vec3 localPoint = Vec3(x, y, z);
	Vec3 worldPoint = transform->localToWorld.MultiplyPoint(localPoint);

	return worldPoint;
}
