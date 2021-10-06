#include "stdafx.h"
#include "TestScene.h"
#include "FPSCharacterController.h"

IClonable* TestScene::Clone()
{
    return new TestScene;
}

void TestScene::OnLoad(Scene* beforeScene)
{
    {
        MaterialParameters params;
        Material::Create(params, L"material", true);
    }

    {   // Load textures
        Texture::CreateFromFile(L"../SharedResourced/Texture/Dev.png");
        Texture::CreateFromFile(L"../SharedResourced/Texture/DevAlpha.png");
        Texture::CreateFromFile(L"../SharedResourced/Texture/DevTransparent.png");
    }

    {   // Create directional light
        auto obj = CreateGameObject();

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));

        obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
        auto light = obj->AddComponent<DirectionalLight>();
        light->ambientFactor = 0.5f;
    }

    // Craete render texture
    auto renderTexture = RenderTexture::CreateRenderTexture(512, 512, Color::white(), L"RenderTexture", false);

    {   // Create quad for render texture
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(2, -1.5f, 0);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
        renderer->SetTexture(0, Resource::FindAs<RenderTexture>(L"RenderTexture"));
        renderer->material = Resource::FindAs<Material>(BuiltInNolightPriorityMaterial);
    }

    {   // Create test player
        auto obj = CreateGameObject();
        auto cameraObj = CreateGameObjectToChild(obj->transform);
        auto controller = cameraObj->AddComponent<FPSCharacterController>();

        {   // Create camera for capture to render texture
            auto subCam = controller->camera->gameObject->AddComponent<Camera>();
            subCam->allowRenderLayers = (1 << 0);
            subCam->cameraOrder = 100;
            subCam->renderTexture = Resource::FindAs<RenderTexture>(L"RenderTexture");
        }
    }

    {   // Create ground
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -3, 0);
        obj->transform->scale = Vec3(100, 1, 100);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
    }

    {   // Create triangle
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(10, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 0);
        obj->transform->scale = Vec3(20, 20, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<RightTriangleCollider>();
    }

    {   // Create rotated ground
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, 0, 10);
        obj->transform->eulerAngle = Vec3(-20, 0, 0);
        obj->transform->scale = Vec3(20, 1, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
    }

    {   // Create wall
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(-10, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 90);
        obj->transform->scale = Vec3(20, 1, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
    }

    //{   // Create Orthographic projection camera
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(-1000, -1000, -10);
    //    
    //    auto camera = obj->AddComponent<Camera>();
    //    camera->cameraOrder = 10000;
    //    camera->overlapMode = true;
    //    camera->allowRenderLayers = (1 << 5);
    //    camera->projectionMode = ProjectionMode::Orthographic;
    //}

    //{   // Create quat for Orthographic projection camera
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec2(-1000, -1000);
    //    obj->transform->scale = Vec3::one();

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
    //    renderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
    //    renderer->renderLayerIndex = 5;
    //}
}

void TestScene::OnUnload(Scene* nextScene)
{
}
