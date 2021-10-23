#include "stdafx.h"
#include "TestSceneSeob.h"
#include "Player.h"
#include "Skybox.h"
#include "TotalLoad.h"

IClonable* TestSceneSeob::Clone()
{
	return new TestSceneSeob;
}

void TestSceneSeob::OnLoad(Scene* beforeScene)
{
	{
		auto skyboxObj = CreateGameObject();
		Skybox* skybox = skyboxObj->AddComponent<Skybox>();

		skybox->SetTopTexture(L"../SharedResource/Texture/skybox_cloudy/top.png");
		skybox->SetLeftTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
		skybox->SetRightTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
		skybox->SetForwardTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
		skybox->SetBackTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
		skybox->SetBottomTexture(L"../SharedResource/Texture/skybox_cloudy/bottom.png");
	}

	{   // Create test player
		auto obj = CreateGameObject();
		auto controller = obj->AddComponent<Player>();
	}

	TotalLoad::Load(L"../Data/Total/1022testmap.txt");
}

void TestSceneSeob::OnUnload(Scene* nextScene)
{
}
