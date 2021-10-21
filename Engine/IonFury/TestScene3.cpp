#include "stdafx.h"
#include "TestScene3.h"
#include "Player.h"
#include "Skybox.h"
#include "Deacon.h"
#include "Drone.h"
#include "MapLoad.h"
#include "ObjectContainer.h"
#include "ObjectGetItem.h"
#include "Mutant.h"
#include "BasicMutant.h"
#include "Skull.h"

IClonable* TestScene3::Clone()
{
	return new TestScene3;
}

void TestScene3::OnLoad(Scene* beforeScene)
{
	AddSkyBox();
	AddMonster();
	AddMap();
	//  MapLoad::LoadMap(L"../Data/Map/testmap.txt");



	//{ //컨테이너
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(0.f, 0.f, 0.f);
	//	obj->transform->localPosition = Vec3(0, -1.5f, 0);
	//	obj->transform->scale = Vec3(2.f, 2.f, 2.f);
	//	auto* wooden = obj->AddComponent<ObjectContainer>();
	//	wooden->SetLeftTexture(L"../SharedResource/Texture/object/Container/123.png");
	//	wooden->SetRightTexture(L"../SharedResource/Texture/object/Container/123.png");
	//	wooden->SetTopTexture(L"../SharedResource/Texture/object/Container/123.png");
	//	wooden->SetBottomTexture(L"../SharedResource/Texture/object/Container/123.png");
	//	wooden->SetForwardTexture(L"../SharedResource/Texture/object/Container/456.png");
	//	wooden->SetBackTexture(L"../SharedResource/Texture/object/Container/456.png");

	//	auto collider = obj->AddComponent<BoxCollider>();
	//	collider->friction = 1.0f;
	//	collider->restitution = 1.0f;
	//}

	//{ //컨테이너
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(4.f, -2.f, 0.f);
	//	obj->transform->scale = Vec3(1.5f, 1.5f, 1.5f);
	//	//obj->transform->localPosition = Vec3(0, -1.5f, 0);
	//	auto* wooden = obj->AddComponent<ObjectContainer>();
	//	wooden->SetLeftTexture(L"../SharedResource/Texture/object/Container/789.png");
	//	wooden->SetRightTexture(L"../SharedResource/Texture/object/Container/789.png");
	//	wooden->SetTopTexture(L"../SharedResource/Texture/object/Container/789.png");
	//	wooden->SetBottomTexture(L"../SharedResource/Texture/object/Container/789.png");
	//	wooden->SetForwardTexture(L"../SharedResource/Texture/object/Container/987.png");
	//	wooden->SetBackTexture(L"../SharedResource/Texture/object/Container/987.png");

	//	auto collider = obj->AddComponent<BoxCollider>();
	//	collider->friction = 1.0f;
	//	collider->restitution = 1.0f;

	//}

	//{ //컨테이너
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(8.f, -2.f, 0.f);
	//	obj->transform->scale = Vec3(1.5f, .5f, 2.5f);
	//	// obj->transform->localPosition = Vec3(0, -3.5f, 0);
	//	auto* wooden = obj->AddComponent<ObjectContainer>();
	//	wooden->SetLeftTexture(L"../SharedResource/Texture/object/Container/111.png");
	//	wooden->SetRightTexture(L"../SharedResource/Texture/object/Container/111.png");
	//	wooden->SetTopTexture(L"../SharedResource/Texture/object/Container/111.png");
	//	wooden->SetBottomTexture(L"../SharedResource/Texture/object/Container/111.png");
	//	wooden->SetForwardTexture(L"../SharedResource/Texture/object/Container/222.png");
	//	wooden->SetBackTexture(L"../SharedResource/Texture/object/Container/222.png");

	//	auto collider = obj->AddComponent<BoxCollider>();
	//	collider->friction = 1.0f;
	//	collider->restitution = 1.0f;
	//}

	//{   // Create obstacle
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(0, -2, -3);
	//	obj->transform->scale = Vec3(15, 1, 1);

	//	auto renderer = obj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

	//	auto body = obj->AddComponent<Rigidbody>();
	//	body->isKinematic = true;

	//	auto collider = obj->AddComponent<BoxCollider>();
	//	collider->friction = 1.0f;
	//	collider->restitution = 1.0f;
	//}


	//{
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(-10.f, 0.f, 0.f);
	//	auto texture = obj->AddComponent<ObjectGetItem>();
	//	auto renderer = obj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/object/trashcan0.png"));
	//}


}

void TestScene3::OnUnload(Scene* nextScene)
{
}

void TestScene3::AddSkyBox()
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
}

void TestScene3::AddMonster()
{

	  {
	  auto obj = CreateGameObject();
      obj->transform->position = Vec3(-0, 0, -0);
	  obj->transform->eulerAngle = Vec3(0, 0, 0);
      obj->AddComponent<Skull>();
  }
// 
	//for (int i = 0; i < 4; ++i)
	//{

	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(i , 1, 0); //+ Vec3(-10, 0, -10);
	//	obj->AddComponent<Deacon>();

	//}
	//for (int i = 0; i < 15; ++i)
	//{
		//auto obj = CreateGameObject();
		//obj->transform->position = Vec3(i * 2, 0, 0);
		//obj->AddComponent<Mutant>();
	//}

	//{
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(0, 0, -17);
	//	obj->AddComponent<Mutant>();
	//}

	//{
	//	auto obj = CreateGameObject();
	//	obj->transform->position = Vec3(0, 0, -17);
	//	obj->AddComponent<BasicMutant>();
	//}
}

void TestScene3::AddMap()
{

	{   // Create test player
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, 0, -20);
		auto controller = obj->AddComponent<Player>();
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


	{   // Create ground
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, -3, 0);
		obj->transform->scale = Vec3(1000, 1, 1000);

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

		auto body = obj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = obj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
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
		collider->restitution = 1.0f;
	}

	{   // Create obstacle
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, -1, -3);
		obj->transform->scale = Vec3(7.5f, 1, 1);

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

		auto body = obj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = obj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
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
	//    collider->friction = 1.0f;
	//    collider->restitution = 1.0f;
	//}

	{   // Create rotated ground
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, 0, 10);
		obj->transform->eulerAngle = Vec3(-20, 0, 0);
		obj->transform->scale = Vec3(30, 1, 30);

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
		auto body = obj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = obj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

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
	//    collider->friction = 1.0f;
	//    collider->restitution = 1.0f;
	//}

	{   // Create wall
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(+15, 0, 0);
		obj->transform->eulerAngle = Vec3(0, 0, 90);
		obj->transform->scale = Vec3(40, 1, 40);

		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
		auto body = obj->AddComponent<Rigidbody>();
		body->isKinematic = true;

		auto collider = obj->AddComponent<BoxCollider>();
		collider->friction = 1.0f;
		collider->restitution = 1.0f;
	}

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
	//    collider->friction = 1.0f;
	//    collider->restitution = 1.0f;
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
	//    collider->friction = 1.0f;
	//    collider->restitution = 1.0f;
	//}

}

