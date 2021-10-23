#include "stdafx.h"
#include "TestScene2.h"
#include "Player.h"
#include "Skybox.h"
#include "Spider.h"
#include "Drone.h"
#include "Warmech.h"
#include "ObjectVent.h"
#include "Wendigo.h"

IClonable* TestScene2::Clone()
{
	return new TestScene2;
}

void TestScene2::OnLoad(Scene* beforeScene)
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
		light->ambientFactor = 0.5f;
	}

	{   // Create test player
		auto obj = CreateGameObject();
		auto controller = obj->AddComponent<Player>();
	}

	//{    // Create Object
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(0, -1.7f, 3);
	//    obj->transform->scale = Vec3(2, 1, 1);
	//    obj->AddComponent<ObjectVent>();
	//}

	{   // Create ground
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, -3, 0);
		obj->transform->scale = Vec3(100, 1, 100);

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

		auto body = obj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = obj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
	}

	{   // Create obstacle
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, -2, -3);
		obj->transform->scale = Vec3(15, 1, 1);

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

		auto body = obj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = obj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
	}

	//{   // Create triangle
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(10, 0, 0);
	//    obj->transform->eulerAngle = Vec3(0, 0, 0);
	//    obj->transform->scale = Vec3(20, 10, 20);

	//    auto renderer = obj->AddComponent<UserMeshRenderer>();
	//    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
	//    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
	//    auto body = obj->AddComponent<Rigidbody>();
	//    body->isKinematic = true;
	//    auto collider = obj->AddComponent<RightTriangleCollider>();
	//}

	//{   // Create rotated ground
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(0, 0, 10);
	//    obj->transform->eulerAngle = Vec3(-20, 0, 0);
	//    obj->transform->scale = Vec3(30, 1, 30);

	//    auto renderer = obj->AddComponent<UserMeshRenderer>();
	//    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
	//    auto body = obj->AddComponent<Rigidbody>();
	//    body->isKinematic = true;
	//    auto collider = obj->AddComponent<BoxCollider>();
	//}

	//{   // Create wall
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(-15, 0, 0);
	//    obj->transform->eulerAngle = Vec3(0, 0, 90);
	//    obj->transform->scale = Vec3(40, 1, 40);

	//    auto renderer = obj->AddComponent<UserMeshRenderer>();
	//    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
	//    auto body = obj->AddComponent<Rigidbody>();
	//    body->isKinematic = true;
	//    auto collider = obj->AddComponent<BoxCollider>();
	//}

	//{   // Create wall
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(+15, 0, 0);
	//    obj->transform->eulerAngle = Vec3(0, 0, 90);
	//    obj->transform->scale = Vec3(40, 1, 40);

	//    auto renderer = obj->AddComponent<UserMeshRenderer>();
	//    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
	//    auto body = obj->AddComponent<Rigidbody>();
	//    body->isKinematic = true;
	//    auto collider = obj->AddComponent<BoxCollider>();
	//}

	//{   // Create wall
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(0, 0, -15);
	//    obj->transform->eulerAngle = Vec3(0, 90, 90);
	//    obj->transform->scale = Vec3(40, 1, 40);

	//    auto renderer = obj->AddComponent<UserMeshRenderer>();
	//    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
	//    auto body = obj->AddComponent<Rigidbody>();
	//    body->isKinematic = true;
	//    auto collider = obj->AddComponent<BoxCollider>();
	//}

	//{   // Create wall
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(0, 0, +15);
	//    obj->transform->eulerAngle = Vec3(0, 90, 90);
	//    obj->transform->scale = Vec3(40, 1, 40);

	//    auto renderer = obj->AddComponent<UserMeshRenderer>();
	//    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
	//    auto body = obj->AddComponent<Rigidbody>();
	//    body->isKinematic = true;
	//    auto collider = obj->AddComponent<BoxCollider>();
	//}

	//{
	//    auto obj = CreateGameObject();
	//    obj->transform->position = Vec3(0, 2, -5);
	//    obj->AddComponent<Warmech>();
	//}

	//for (int i = 0; i < 5; ++i)
	//{
	//	for (int j = 0; j < 5; ++j)
	//	{
	//		auto obj = CreateGameObject();
	//		obj->transform->position = Vec3(i * 4, 2, j * 4) + Vec3(-10, 0, -10);
	//		obj->transform->eulerAngle = Vec3(0, 90, 0);
	//		obj->AddComponent<Drone>();
	//		//obj->AddComponent<Spider>();
	//	}
	//}
	// 
	{
	    auto obj = CreateGameObject();
	    obj->transform->position = Vec3(0, 2, -10);
	    obj->AddComponent<Wendigo>();
	}

}

void TestScene2::OnUnload(Scene* nextScene)
{
}
