#include "shared_stdafx.h"
#include "SceneMap.h"
#include "TotalLoad.h"
#include "Skybox.h"

void SceneMap::LoadNextScene()
{
    SceneManager::ChangeScene(GetNextScene());
}

void SceneMap::OnLoad(Scene* beforeScene)
{
	TotalLoad::Load(GetMapLocalPath());

    {
        auto skyboxObj = CreateGameObject();
        m_skybox = skyboxObj->AddComponent<Skybox>();

        m_skybox->SetTopTexture(L"../SharedResource/Texture/skybox_cloudy/top.png");
        m_skybox->SetLeftTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        m_skybox->SetRightTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        m_skybox->SetForwardTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        m_skybox->SetBackTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        m_skybox->SetBottomTexture(L"../SharedResource/Texture/skybox_cloudy/bottom.png");
    }
}

void SceneMap::OnUnload(Scene* nextScene)
{
}
