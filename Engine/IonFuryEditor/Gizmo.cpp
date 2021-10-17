#include "IonFuryEditorBase.h"
#include "Gizmo.h"
#include "EditorManager.h"
#include "Pickable.h"

void Gizmo::Awake()
{
	MaterialParameters param;
	param.renderQueue = RenderQueue::GeometryLast;
	param.zRead = false;
	param.zWrite = false;
	param.useLight = false;
	m_gizmoMaterial = Material::CreateUnmanaged(param);

	UserMesh::Create<CubeUserMesh>(L"../Resource/Gizmo/CubeUserMesh.mesh", true);
	Texture::CreateInDirectX(128, 128, Color::red(), L"../Resource/RedTexture.png", true);
	Texture::CreateInDirectX(128, 128, Color::green(), L"../Resource/GreenTexture.png", true);
	Texture::CreateInDirectX(128, 128, Color::blue(), L"../Resource/BlueTexture.png", true);

	auto gizmoCubeMesh = Resource::FindAs<UserMesh>(L"../Resource/Gizmo/CubeUserMesh.mesh");
	auto redTex = Resource::FindAs<Texture>(L"../Resource/RedTexture.png");
	auto greenTex = Resource::FindAs<Texture>(L"../Resource/GreenTexture.png");
	auto blueTex = Resource::FindAs<Texture>(L"../Resource/BlueTexture.png");

	m_gizmoParentObj = CreateGameObject();
	m_gizmoParentObj->transform->parent = gameObject->transform;

	for (int i = 2; i >= 0; --i)
	{
		m_axisObj[i] = CreateGameObject();
		m_axisObj[i]->transform->parent = m_gizmoParentObj->transform;
		m_renderer[i] = m_axisObj[i]->AddComponent<UserMeshRenderer>();
		m_renderer[i]->userMesh = gizmoCubeMesh;
		m_renderer[i]->material = m_gizmoMaterial;
	}

	m_renderer[GIZMO_AXIS_X]->SetTexture(0, redTex);
	m_renderer[GIZMO_AXIS_Y]->SetTexture(0, greenTex);
	m_renderer[GIZMO_AXIS_Z]->SetTexture(0, blueTex);

	ResetGizmoTransform();
}

void Gizmo::Update()
{
	if (Input::GetKeyDown(Key::LeftMouse))
	{
		PickHandle();
	}
	else if (HasSelect() && Input::GetKey(Key::LeftMouse))
	{
		Handling();
		m_Handling = true;
	}
	if (Input::GetKeyUp(Key::LeftMouse))
	{
		PutHandle();
		m_Handling = false;
	}
}

void Gizmo::OnDestroy()
{
	if (m_gizmoMaterial)
	{
		m_gizmoMaterial->ReleaseUnmanaged();
		m_gizmoMaterial = nullptr;
	}
}

void Gizmo::Click()
{
	if (Input::GetKeyDown(Key::LeftMouse))
	{
		PickHandle();
	}
	else if (HasSelect() && Input::GetKey(Key::LeftMouse))
	{
		Handling();
		m_Handling = true;
	}
	if (Input::GetKeyUp(Key::LeftMouse))
	{
		PutHandle();
		m_Handling = false;
	}
}

bool Gizmo::PickHandle()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	// X, Y, Z ���� ����� ����ĳ��Ʈ�ؼ� 
	// ���õǾ����� Ȯ���մϴ�.
	for (int i = 0; i < GIZMO_AXIS_NONE; ++i)
	{
		Vec3 hit;
		if (m_renderer[i]->Raycast(hit, rayPoint, rayDir))
		{
			// ���� ���õǾ��ٸ�

			// ���õ� ���� �����մϴ�.
			m_select = (GIZMO_AXIS)i;

			// ���콺�� ���� ������ ��ġ�� �����մϴ�.
			m_selectCoord = CalcGizmoHandlingCoord();

			// ���� ���õǾ������� ������Ʈ �߽� ��ġ�� �����մϴ�.
			m_selectedPosition = transform->position;

			return true;
		}
	}
	return false;
}

void Gizmo::PutHandle()
{
	m_select = GIZMO_AXIS_NONE;
}

bool Gizmo::HasSelect() const
{
	return m_select != GIZMO_AXIS_NONE;
}

bool Gizmo::HasAxisX() const
{
	return m_select == GIZMO_AXIS_X;
}

bool Gizmo::HasAxisY() const
{
	return m_select == GIZMO_AXIS_Y;
}

bool Gizmo::HasAxisZ() const
{
	return m_select == GIZMO_AXIS_Z;
}

void Gizmo::Attach(Transform* root)
{
	Detach();

	gameObject->activeSelf = true;

	root = root->GetRoot();

	transform->position = root->position;
	root->parent = transform;
	ResetGizmoTransform();

	m_selectedTransform = root;
}

void Gizmo::Detach()
{
	if (m_selectedTransform)
	{
		m_selectedTransform->parent = nullptr;

		m_selectedTransform.Reset();
	}

	gameObject->activeSelf = false;
}

Transform* Gizmo::GetSelectedObject() const
{
	return m_selectedTransform.GetPointer();
}

void Gizmo::DeleteAttachedObject()
{
	if (m_selectedTransform)
	{
		m_selectedTransform->gameObject->Destroy();
		int test = 0;
	}
	m_selectedTransform.Reset();
}

void Gizmo::ChangeTextureAttachedObject(CString texturePath)
{
	if (m_selectedTransform)
	{
		UserMeshRenderer* renderer = m_selectedTransform->gameObject->GetComponent<Pickable>()->GetRenderer();
		renderer->SetTexture(0, Resource::Find(texturePath.GetString())->GetReferenceTo<Texture>());
	};
}

void Gizmo::GetInformation()
{
	if (m_selectedTransform)
	{
		UserMeshRenderer* renderer = m_selectedTransform->gameObject->GetComponent<Pickable>()->GetRenderer();
		wstring meshPath = renderer->GetUserMesh()->GetLocalPath();
		wstring texPath = renderer->GetTexture(0)->GetLocalPath();	//settexture�Ҷ��� 0���� ������ϱ�
	}
}

bool Gizmo::GetHandlingState()
{
	return m_Handling;
}

void Gizmo::ResetGizmoTransform()
{
	m_gizmoParentObj->transform->eulerAngle = Vec3::zero();
	m_gizmoParentObj->transform->localPosition = Vec3::zero();

	for (int i = 0; i < 3; ++i)
	{
		m_axisObj[i]->transform->localEulerAngle = Vec3::zero();
		m_axisObj[i]->transform->localPosition = Vec3::zero();
	}

	float width = 0.1f;

	m_axisObj[GIZMO_AXIS_X]->transform->localScale = Vec3(2, width, width);
	m_axisObj[GIZMO_AXIS_Y]->transform->localScale = Vec3(width, 2, width);
	m_axisObj[GIZMO_AXIS_Z]->transform->localScale = Vec3(width, width, 2);
}

void Gizmo::Handling()
{
	float gap = 0.2f;

	Vec3 dragCoord = CalcGizmoHandlingCoord();
	Vec3 delta = dragCoord - m_selectCoord;

	transform->position = m_selectedPosition + delta;

	if (Input::GetKey(Key::LCtrl))
	{
		Vec3 pos = transform->position;
		switch (m_select)
		{
		case GIZMO_AXIS_X:
			pos.x = int(pos.x / gap) * gap;
			break;
		case GIZMO_AXIS_Y:
			pos.y = int(pos.y / gap) * gap;
			break;
		case GIZMO_AXIS_Z:
			pos.z = int(pos.z / gap) * gap;
			break;
		}
		transform->position = pos;
	}
}

Vec3 Gizmo::CalcGizmoHandlingCoord()
{
	D3DXPLANE plane;
	Vec3 center = transform->position;
	Vec3 v1, v2;

	auto mainCamera = Camera::GetMainCamera();

	// For support world rotation
	switch (m_select)
	{
		case GIZMO_AXIS_X:
			v1 = center + Vec3::right();
			v2 = center + mainCamera->transform->up;
			break;
		case GIZMO_AXIS_Y:
			v1 = center + Vec3::up();
			v2 = center + mainCamera->transform->right;
			break;
		case GIZMO_AXIS_Z:
			v1 = center + Vec3::forawrd();
			v2 = center + mainCamera->transform->up;
			break;
		default:
			return center;
	}

	//// For support local rotation
	//switch (m_select)
	//{
	//	case GIZMO_AXIS_X:
	//		v1 = center + transform->right;
	//		v2 = center + mainCamera->transform->up;
	//		break;
	//	case GIZMO_AXIS_Y:
	//		v1 = center + transform->up;
	//		v2 = center + mainCamera->transform->forward;
	//		break;
	//	case GIZMO_AXIS_Z:
	//		v1 = center + transform->forward;
	//		v2 = center + mainCamera->transform->up;
	//		break;
	//	default:
	//		return center;
	//}

	Vec3 cv1 = Vec3(v1 - center);
	Vec3 cv2 = Vec3(v2 - center);
	Vec3 planeNormal = Vec3::Cross(cv1, cv2).normalized();
	Vec3 planePoint = center;
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	float t = RaycastOnPlane(planeNormal, planePoint, rayPoint, rayDir);
	Vec3 pointOnPlane = rayPoint + rayDir * t;

	Vec3 pointOnSelectAxis = Vec3::ProjectOnVec3(pointOnPlane - center, cv1) + center;

	return pointOnSelectAxis;
}
