#include "IonFuryEditorBase.h"
#include "EditorScene.h"
#include "EditorManager.h"

IClonable* EditorScene::Clone()
{
    // 씬을 다시 시작하려는 경우에
    // 새로운 씬을 넘겨야 합니다.
    // 그 때 사용되는 부분입니다.
    return new EditorScene;
}

void EditorScene::OnLoad(Scene* beforeScene)
{
    UserMesh::Create<CubeUserMesh>(L"../Resource/CubeUserMesh.mesh", true);
    UserMesh::Create<SphereUserMesh>(L"../Resource/SphereUserMesh.mesh", true);
    UserMesh::Create<CyilinderUserMesh>(L"../Resource/CyilinderUserMesh.mesh", true);
    UserMesh::Create<QuadUserMesh>(L"../Resource/QuadUserMesh.mesh", true);
    Texture::CreateFromFile(L"../SharedResourced/Texture/Dev.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevAlpha.png");
    Texture::CreateFromFile(L"../SharedResourced/Texture/DevTransparent.png");

    // 백버퍼의 색상을 설정합니다.
    GraphicDevice::GetInstance()->SetBackgroundColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

    // 에디터 매니저 컴포넌트를 생성합니다.
    GameObject* editorManagerObj = CreateGameObject(L"EditorManager");
    editorManagerObj->AddComponent<EditorManager>();

    
}

void EditorScene::OnUnload(Scene* nextScene)
{
}
