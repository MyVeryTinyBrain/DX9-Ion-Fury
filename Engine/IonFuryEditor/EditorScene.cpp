#include "IonFuryEditorBase.h"
#include "EditorScene.h"
#include "EditorManager.h"
#include "Gizmo.h"

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

    Texture::CreateFromFile(L"../SharedResource/Texture/Light.png");
    Texture::CreateFromFile(L"../SharedResource/Texture/object/brick.jpg");

    // ������� ������ �����մϴ�.
    GraphicDevice::GetInstance()->SetBackgroundColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

    // ������ �Ŵ��� ������Ʈ�� �����մϴ�.
    GameObject* editorManagerObj = CreateGameObject(L"EditorManager");
    editorManagerObj->AddComponent<EditorManager>();

    Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
    giz->Detach();
    giz->enable = false;
}

void EditorScene::OnUnload(Scene* nextScene)
{
}
