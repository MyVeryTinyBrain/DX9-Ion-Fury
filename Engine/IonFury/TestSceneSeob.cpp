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

	{   // Create directional light
		auto obj = CreateGameObject();

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

		obj->transform->position = Vec3(0, 5, 0);
		obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
		auto light = obj->AddComponent<DirectionalLight>();
		light->ambientFactor = 0.6f;
	}

	{   // Create test player
		auto obj = CreateGameObject();
		auto controller = obj->AddComponent<Player>();
	}

	TotalLoad::Load(L"../Data/Total/TestMap.txt");
}

void TestSceneSeob::OnUnload(Scene* nextScene)
{
}
