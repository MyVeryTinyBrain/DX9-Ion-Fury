#pragma once

#include "Trigger.h"

class BossEnemySpawnTrigger : public Trigger
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:

	static void EnableAll();

	static void DisableAll();

private:

	Vec3 GetRandomPointInBox() const;

private:

	float m_spawnDelay = 5.0f;

	float m_spawnTimer = m_spawnDelay;

private:

	static std::vector<BossEnemySpawnTrigger*> g_triggers;
};

