#include "stdafx.h"
#include "TestBeginScene.h"
#include "CamController.h"

IClonable* TestBeginScene::Clone()
{
    return new TestBeginScene;
}

void TestBeginScene::OnLoad(Scene* beforeScene)
{
    Texture::CreateFromFile(L"../SharedResourced/Texture/Dev.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevAlpha.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevTransparent.png"); 

    GraphicDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

    //Light::SetAmbientLight(Color::white());

    GameObject* cameraObj = CreateGameObject();
    cameraObj->transform->position = Vec3(0, 0, -2);
    cameraObj->AddComponent<Camera>();
    cameraObj->AddComponent<CamController>();

    //auto directionalLightObj = CreateGameObject();
    //auto dl = directionalLightObj->AddComponent<DirectionalLight>();
    //dl->color = Color::white() * 0.8f;
    //dl->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();

    {
        GameObject* obj = CreateGameObject();
        obj->transform->scale = Vec3(10, 1, 10);
        auto col = obj->AddComponent<BoxCollider>();
        col->extents = Vec3(1, 1, 1);
        auto body = obj->AddComponent<Rigidbody>();
        body->SetKinematic(true);
        body->SetPosition(Vec3(0, -3, 0));
        auto r = obj->AddComponent<UserMeshRenderer>();
        r->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
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
        r->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        r->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
    }
}

void TestBeginScene::OnUnload(Scene* nextScene)
{
}
