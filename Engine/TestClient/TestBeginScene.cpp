#include "stdafx.h"
#include "TestBeginScene.h"
#include "CamController.h"
#include "Rotater.h"
#include "LinkByLine.h"
#include "Releaser.h"
#include "Stalking.h"
#include "Player.h"
#include "EventTest.h"
#include "../Engine/header/RightTriangleUserMesh.h"
#include "../Engine/header/TriangleUserMesh.h"

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
    UserMesh::Create<CapsuleUserMesh>(L"../Resource/CapsuleUserMesh.mesh", true);
    UserMesh::Create<RightTriangleUserMesh>(L"../Resource/RightTriangleUserMesh.mesh", true);
    UserMesh::Create<TriangleUserMesh>(L"../Resource/TriangleUserMesh.mesh", true);
    Texture::CreateFromFile(L"../SharedResourced/Texture/Dev.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevAlpha.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevTransparent.png"); 

    GraphicDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

    //Light::SetAmbientLight(Color::white());

    GameObject* cameraObj = CreateGameObject();
    cameraObj->transform->position = Vec3(0, 0, -2);
    cameraObj->AddComponent<Camera>();
    cameraObj->AddComponent<CamController>();

    auto directionalLightObj = CreateGameObject();
    auto dl = directionalLightObj->AddComponent<DirectionalLight>();
    dl->color = Color::white() * 0.8f;
    dl->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();

    {
        GameObject* obj = CreateGameObject();
        obj->transform->scale = Vec3(10, 1, 10);
        auto col = obj->AddComponent<BoxCollider>();
        col->extents = Vec3(1, 1, 1);
        auto body = obj->AddComponent<Rigidbody>();
        body->SetKinematic(true);
        body->SetPosition(Vec3(0, -3, 0));
        auto r = obj->AddComponent<UserMeshRenderer>();
        r->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
        r->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
    }

    {
        GameObject* obj = CreateGameObject();
        obj->transform->scale = Vec3(1000, 1, 1000);
        auto col = obj->AddComponent<BoxCollider>();
        col->extents = Vec3(1, 1, 1);
        auto body = obj->AddComponent<Rigidbody>();
        body->SetKinematic(true);
        body->SetPosition(Vec3(0, -10, 0));
        auto r = obj->AddComponent<UserMeshRenderer>();
        r->userMesh = Resource::FindAs<UserMesh>(L"../Resource/CubeUserMesh.mesh");
        r->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
    }
}

void TestBeginScene::OnUnload(Scene* nextScene)
{
}
