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
#include "Gizmo.h"
#include "EditorEnum.h"
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
}

// DlgObjectTool 메시지 처리기

BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
END_MESSAGE_MAP()

