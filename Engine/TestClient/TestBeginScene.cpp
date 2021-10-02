#include "stdafx.h"
#include "TestBeginScene.h"
#include "CamController.h"
#include "Rotater.h"
#include "LinkByLine.h"
#include "Releaser.h"
#include "Stalking.h"
#include "Player.h"
#include "EventTest.h"

IClonable* TestBeginScene::Clone()
{
    return new TestBeginScene;
}

void TestBeginScene::OnLoad(Scene* beforeScene)
{
    UserMesh::Create<CubeUserMesh>(L"../Resource/CubeUserMesh.mesh", true);
    UserMesh::Create<SphereUserMesh>(L"../Resource/SphereUserMesh.mesh", true);
    UserMesh::Create<CyilinderUserMesh>(L"../Resource/CyilinderUserMesh.mesh", true);
    UserMesh::Create<QuadUserMesh>(L"../Resource/QuadUserMesh.mesh", true);
    Texture::CreateFromFile(L"../SharedResourced/Texture/Dev.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevAlpha.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevTransparent.png"); 

    GraphicDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

    //Light::SetAmbientLight(Color::white() * 0.1f);

    GameObject* cameraObj = CreateGameObject();
    cameraObj->transform->position = Vec3(0, 0, -2);
    cameraObj->AddComponent<Camera>();
    cameraObj->AddComponent<CamController>();

    GameObject* lightObj = CreateGameObject();
    lightObj->transform->position = Vec3(0, 0, -3.5f);
    lightObj->AddComponent<SpotLight>()->color = Color::white();
    lightObj->transform->parent = cameraObj->transform;

    //GameObject* obj1 = CreateGameObject();
    //obj1->transform->position = Vec3(0, 0, 0.0f);
    //auto cubeRenderer1 = obj1->AddComponent<UserMeshRenderer>();
    //cubeRenderer1->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
    //cubeRenderer1->SetTexture(0, Resource::Find(L"../SharedResourced/Texture/Dev.png")->GetReferenceTo<Texture>());

    GameObject* obj1 = CreateGameObject();
    obj1->transform->position = Vec3(0, 0, 0);
    obj1->AddComponent<Player>();
    obj1->name = L"obj1";

    GameObject* obj2 = CreateGameObject();
    obj2->transform->position = Vec3(10, 0, 0);
    obj2->AddComponent<Player>()->SetArmLocalAngle(45);
    obj2->name = L"obj2";

    auto obj3 = CreateGameObject();
    obj3->AddComponent<EventTest>();
}

void TestBeginScene::OnUnload(Scene* nextScene)
{
}
