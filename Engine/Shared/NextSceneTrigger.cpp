#include "shared_stdafx.h"
#include "NextSceneTrigger.h"
#include "Player.h"
#include "PlayerUI.h"
#include "SceneMap.h"
#include "AmmoBackup.h"

void NextSceneTrigger::LateUpdate()
{
	if (m_endFade)
	{
		Scene* scene = SceneManager::GetCurrentScene();
		SceneMap* sceneMap = dynamic_cast<SceneMap*>(scene);

		if (sceneMap)
		{
			AmmoBackup::GetInstance()->Backup();

			sceneMap->LoadNextScene();
		}

		gameObject->activeSelf = false;
		return;
	}

	if (m_beginFade && !m_endFade)
	{
		float fade = Player::GetInstance()->UI->GetFadeAlpha();

		if (fade >= 1.0f)
		{
			m_endFade = true;
		}
	}
}

void NextSceneTrigger::OnUse()
{
	Player::GetInstance()->UI->FadeIn();

	m_beginFade = true;
}
