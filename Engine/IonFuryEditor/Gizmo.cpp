#include "IonFuryEditorBase.h"
#include "Gizmo.h"
#include "EditorManager.h"

void Gizmo::Awake()
{
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

	for (int i = 0; i < 3; ++i)
	{
		m_axisObj[i] = CreateGameObject();
		m_axisObj[i]->transform->parent = m_gizmoParentObj->transform;
		m_renderer[i] = m_axisObj[i]->AddComponent<UserMeshRenderer>();
		m_renderer[i]->userMesh = gizmoCubeMesh;
		m_renderer[i]->allowLighting = false;
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
	}
	if (Input::GetKeyUp(Key::LeftMouse))
	{
		PutHandle();
	}
}

bool Gizmo::PickHandle()
{
	Vec3 rayPoint, rayDir;
	Input::GetMouseWorldRay(rayPoint, rayDir);

	// X, Y, Z 축의 기즈모에 레이캐스트해서 
	// 선택되었는지 확인합니다.
	for (int i = 0; i < GIZMO_AXIS_NONE; ++i)
	{
		Vec3 hit;
		if (m_renderer[i]->Raycast(hit, rayPoint, rayDir))
		{
			// 축이 선택되었다면

			// 선택된 축을 저장합니다.
			m_select = (GIZMO_AXIS)i;

			// 마우스가 축을 선택한 위치를 저장합니다.
			m_selectCoord = CalcGizmoHandlingCoord();

			// 축이 선택되었을때의 오브젝트 중심 위치를 저장합니다.
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
	Vec3 dragCoord = CalcGizmoHandlingCoord();
	Vec3 delta = dragCoord - m_selectCoord;
	transform->position = m_selectedPosition + delta;
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
