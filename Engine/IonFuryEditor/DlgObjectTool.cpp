// DlgObjectTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "afxdialogex.h"
#include "DlgObjectTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "Pickable.h"
#include "HandlingObject.h"
#include "Gizmo.h"
#include "EditorEnum.h"
//#include "../IonFury/"
//
#include <fstream>
#include <atlconv.h>


// DlgObjectTool 대화 상자

IMPLEMENT_DYNAMIC(DlgObjectTool, CDialog)

DlgObjectTool::DlgObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgObjTool, pParent)
	, m_Name(_T(""))
{

}

DlgObjectTool::~DlgObjectTool()
{
}

void DlgObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ObjectListBox);
	DDX_Control(pDX, IDC_SLIDER2, m_ScaleXSlider);
	DDX_Control(pDX, IDC_SLIDER4, m_ScaleYSlider);
	DDX_Control(pDX, IDC_SLIDER5, m_ScaleZSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_RotationXSlider);
	DDX_Control(pDX, IDC_SLIDER6, m_RotationYSlider);
	DDX_Control(pDX, IDC_SLIDER11, m_RotationZSlider);
	DDX_Control(pDX, IDC_SLIDER1, m_PivotScaleSlider);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Control(pDX, IDC_COMBO1, m_TypeComboBox);
}

// DlgObjectTool 메시지 처리기

BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON17, &DlgObjectTool::OnBnClickedAddButton)
END_MESSAGE_MAP()


BOOL DlgObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_TypeComboBox.AddString(_T("ItemBowAmmo"));

	m_TypeComboBox.AddString(_T("ItemChaingunAmmo"));

	m_TypeComboBox.AddString(_T("ItemLauncherAmmo"));

	m_TypeComboBox.AddString(_T("ItemRevolverAmmo"));

	m_TypeComboBox.AddString(_T("ItemShotgunAmmo"));

	m_TypeComboBox.AddString(_T("ItemSMGAmmo"));

	m_TypeComboBox.AddString(_T("ItemHealthPack"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgObjectTool::OnBnClickedAddButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HandlingObject* Pivot = EditorManager::GetInstance()->GetPerspectiveCamera()->Add_HandlingObject(m_Cnt);
	++m_Cnt;

	CString Type = L"";
	m_TypeComboBox.GetLBText(m_TypeComboBox.GetCurSel(), Type);
	Pivot->AddTypeToChildObject(Type);
}


