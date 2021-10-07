#include "IonFuryEditorBase.h"
#include "EditorScene.h"
#include "EditorManager.h"

IClonable* EditorScene::Clone()
{
    // ���� �ٽ� �����Ϸ��� ��쿡
    // ���ο� ���� �Ѱܾ� �մϴ�.
    // �� �� ���Ǵ� �κ��Դϴ�.
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

    // ������� ������ �����մϴ�.
    GraphicDevice::GetInstance()->SetBackgroundColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

    // ������ �Ŵ��� ������Ʈ�� �����մϴ�.
    GameObject* editorManagerObj = CreateGameObject(L"EditorManager");
    editorManagerObj->AddComponent<EditorManager>();

    
}

void EditorScene::OnUnload(Scene* nextScene)
{
}
