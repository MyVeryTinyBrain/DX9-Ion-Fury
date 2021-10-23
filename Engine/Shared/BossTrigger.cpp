#include "shared_stdafx.h"
#include "BossTrigger.h"
#include "Tags.h"
#include "Names.h"
#include "ObjectAutoDoor.h"

void BossTrigger::Start()
{
	Trigger::Start();

	auto doors = FindGameObjectsWithTag(TAG_DOOR);

	for (auto door : doors)
	{
		if (door->name == NAME_BOSS_ENTRANCE_DOOR)
		{
			m_door = door->GetComponent<ObjectAutoDoor>();
			break;
		}
	}
}

void BossTrigger::OnUse()
{
	if (m_door)
	{
		m_door->Close();
	}
}
