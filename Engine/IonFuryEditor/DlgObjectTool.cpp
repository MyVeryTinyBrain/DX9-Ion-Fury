// DlgObjectTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgObjectTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"

// DlgObjectTool 대화 상자

IMPLEMENT_DYNAMIC(DlgObjectTool, CDialog)

void DlgObjectTool::SetPickableObject(GameObject* gameobject)
{

	m_SelectName = gameobject->name.c_str();

	m_rPosX = gameobject->transform->position.x;
	m_rPosY = gameobject->transform->position.y;
	m_rPosZ = gameobject->transform->position.z;

	m_rRotX = gameobject->transform->eulerAngle.x;
	m_rRotY = gameobject->transform->eulerAngle.y;
	m_rRotZ = gameobject->transform->eulerAngle.z;

	m_rScaleX = gameobject->transform->scale.x;
	m_rScaleY = gameobject->transform->scale.y;
	m_rScaleZ = gameobject->transform->scale.z;

	UpdateData(FALSE);
}
void DlgObjectTool::ResetObjectSize()
{
	m_objectName = L"";

	m_fPosX = 0.f;
	m_fPosY = 0.f;
	m_fPosZ = 0.f;

	m_fScaleX = 1.f;
	m_fScaleY = 1.f;
	m_fScaleZ = 1.f;
}
DlgObjectTool::DlgObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgObjectTool, pParent)
	, m_objectName(_T(""))
	, m_eMesh(COMBOBOX::END)
	, m_fPosX(0.f)
	, m_fPosY(0.f)
	, m_fPosZ(0.f)
	, m_fRotX(0.f)
	, m_fRotY(0.f)
	, m_fRotZ(0.f)
	, m_fScaleX(1.f)
	, m_fScaleY(1.f)
	, m_fScaleZ(1.f)
	, m_meshPath(L"")
	, m_objectTag(_T(""))
	, m_SelectName(_T(""))
	, m_rPosX(0)
	, m_rPosY(0)
	, m_rPosZ(0)
	, m_rRotX(0)
	, m_rRotY(0)
	, m_rRotZ(0)
	, m_rScaleX(0)
	, m_rScaleY(0)
	, m_rScaleZ(0)
{

}

DlgObjectTool::~DlgObjectTool()
{
}

void DlgObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Text(pDX, IDC_EDIT1, m_objectName);
	DDX_Text(pDX, IDC_EDIT2, m_fPosX);
	DDX_Text(pDX, IDC_EDIT3, m_fPosY);
	DDX_Text(pDX, IDC_EDIT4, m_fPosZ);
	DDX_Text(pDX, IDC_EDIT5, m_fRotX);
	DDX_Text(pDX, IDC_EDIT6, m_fRotY);
	DDX_Text(pDX, IDC_EDIT7, m_fRotZ);
	DDX_Text(pDX, IDC_EDIT8, m_fScaleX);
	DDX_Text(pDX, IDC_EDIT9, m_fScaleY);
	DDX_Text(pDX, IDC_EDIT10, m_fScaleZ);
	DDX_Text(pDX, IDC_EDIT17, m_objectTag);
	DDX_Text(pDX, OBJECT_1, m_SelectName);
	DDX_Text(pDX, OBJECT_2, m_rPosX);
	DDX_Text(pDX, OBJECT_8, m_rPosZ);
	DDX_Text(pDX, OBJECT_5, m_rPosY);
	DDX_Text(pDX, OBJECT_3, m_rRotX);
	DDX_Text(pDX, OBJECT_6, m_rRotY);
	DDX_Text(pDX, OBJECT_9, m_rRotZ);
	DDX_Text(pDX, OBJECT_4, m_rScaleX);
	DDX_Text(pDX, OBJECT_7, m_rScaleY);
	DDX_Text(pDX, OBJECT_10, m_rScaleZ);
	
}


BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &DlgObjectTool::OnObjectName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgObjectTool::OnSelectMesh)
	ON_EN_CHANGE(IDC_EDIT2, &DlgObjectTool::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT17, &DlgObjectTool::OnObjectTag)
	ON_EN_CHANGE(IDC_EDIT3, &DlgObjectTool::OnEnChangeEditPosY)
	ON_EN_CHANGE(IDC_EDIT4, &DlgObjectTool::OnEnChangeEditPosZ)
	ON_EN_CHANGE(IDC_EDIT8, &DlgObjectTool::OnEnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EDIT9, &DlgObjectTool::OnEnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EDIT10, &DlgObjectTool::OnEnChangeEditScaleZ)
END_MESSAGE_MAP()


// DlgObjectTool 메시지 처리기


BOOL DlgObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_comboBox.AddString(_T("Cube"));
	m_comboBox.AddString(_T("Cyilinder"));
	m_comboBox.AddString(_T("Quad"));
	m_comboBox.AddString(_T("Sphere"));
	m_comboBox.AddString(_T("Capsule"));
	m_comboBox.AddString(_T("RightTriangle"));
	m_comboBox.AddString(_T("Triangle"));


	m_comboBox.SetCurSel(0);

	m_meshPath = BuiltInCubeUserMesh;




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgObjectTool::OnObjectName()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}


void DlgObjectTool::OnSelectMesh()
{

	UpdateData(TRUE);

	m_eMesh = (COMBOBOX)m_comboBox.GetCurSel();
	

	switch (m_eMesh)
	{
	case DlgObjectTool::COMBOBOX::Cube:
		m_meshPath = BuiltInCubeUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Cyilinder:
		m_meshPath = BuiltInCyilinderUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Quad:
		m_meshPath = BuiltInQuadUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Sphere:
		m_meshPath = BuiltInSphereUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Capsule:
		m_meshPath = BuiltInCapsuleUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::RightTriangle:
		m_meshPath = BuiltInRightTriangleUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Triangle:
		m_meshPath = BuiltInTriangleUserMesh;
		break;
	default:
		break;
	}

	UpdateData(FALSE);

}


void DlgObjectTool::OnEnChangeEditPosX()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}



void DlgObjectTool::OnObjectTag()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}


void DlgObjectTool::OnEnChangeEditPosY()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}


void DlgObjectTool::OnEnChangeEditPosZ()
{
	UpdateData(TRUE);


	//UpdateData(FALSE);
}


void DlgObjectTool::OnEnChangeEditScaleX()
{
	UpdateData(TRUE);

	

	//UpdateData(FALSE);
}


void DlgObjectTool::OnEnChangeEditScaleY()
{
	UpdateData(TRUE);


	//UpdateData(FALSE);
}


void DlgObjectTool::OnEnChangeEditScaleZ()
{
	UpdateData(TRUE);


	//UpdateData(FALSE);
}
