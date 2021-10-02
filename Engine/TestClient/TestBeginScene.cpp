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

    Light::SetAmbientLight(Color::white());

    GameObject* cameraObj = CreateGameObject();
    cameraObj->transform->position = Vec3(0, 2, -2);
    cameraObj->AddComponent<Camera>();
    cameraObj->AddComponent<CamController>();

    GameObject* lightObj = CreateGameObject();
    lightObj->transform->position = Vec3(0, 0, -3.5f);
    lightObj->AddComponent<SpotLight>()->color = Color::white();
    lightObj->transform->parent = cameraObj->transform;

    //{
    //    GameObject* kinematic = CreateGameObject();
    //    kinematic->transform->position = Vec3(0, 1, 0);
    //    kinematic->transform->scale = Vec3(10, 1, 10);
    //    auto body = kinematic->AddComponent<Rigidbody>();
    //    kinematic->AddComponent<BoxCollider>()->extents = Vec3(1, 1, 1);
    //    auto renderer = kinematic->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
    //    body->SetKinematic(true);
    //}
}

void TestBeginScene::OnUnload(Scene* nextScene)
{
}
