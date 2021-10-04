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
}


BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &DlgObjectTool::OnObjectName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgObjectTool::OnSelectMesh)
	ON_EN_CHANGE(IDC_EDIT2, &DlgObjectTool::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT17, &DlgObjectTool::OnObjectTag)
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

}



void DlgObjectTool::OnObjectTag()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}
