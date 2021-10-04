// DlgLightTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgLightTool.h"
#include "afxdialogex.h"


// DlgLightTool 대화 상자

IMPLEMENT_DYNAMIC(DlgLightTool, CDialog)

DlgLightTool::DlgLightTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgLightTool, pParent)
	, m_eLight(COMBOBOX::END)
	, m_fPosX(0.f)
	, m_fPosY(0.f)
	, m_fPosZ(0.f)
	, m_ScaleX(0.f)
	, m_ScaleY(0.f)
	, m_ScaleZ(0.f)
	, m_DirX(0.f)
	, m_DirY(0.f)
	, m_DirZ(0.f)
	, m_ColorRed(0.f)
	, m_ColorGreen(0.f)
	, m_ColorBlue(0.f)
	, m_ColorAlpha(0.f)
{

}

DlgLightTool::~DlgLightTool()
{
}

void DlgLightTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Text(pDX, IDC_EDIT1, m_fPosX);
	DDX_Text(pDX, IDC_EDIT2, m_fPosY);
	DDX_Text(pDX, IDC_EDIT3, m_fPosZ);
	DDX_Text(pDX, IDC_EDIT4, m_ScaleX);
	DDX_Text(pDX, IDC_EDIT5, m_ScaleY);
	DDX_Text(pDX, IDC_EDIT6, m_ScaleZ);
	DDX_Text(pDX, IDC_EDIT7, m_DirX);
	DDX_Text(pDX, IDC_EDIT10, m_DirY);
	DDX_Text(pDX, IDC_EDIT18, m_DirZ);
	DDX_Text(pDX, IDC_EDIT9, m_ColorRed);
	DDX_Text(pDX, IDC_EDIT11, m_ColorGreen);
	DDX_Text(pDX, IDC_EDIT12, m_ColorBlue);
	DDX_Text(pDX, IDC_EDIT13, m_ColorAlpha);
}


BEGIN_MESSAGE_MAP(DlgLightTool, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgLightTool::OnSelectLight)
END_MESSAGE_MAP()


// DlgLightTool 메시지 처리기

BOOL DlgLightTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	m_comboBox.AddString(_T("Point"));
	m_comboBox.AddString(_T("Spot"));
	m_comboBox.AddString(_T("Directional"));
	m_comboBox.AddString(_T("Ambient"));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgLightTool::OnSelectLight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_eLight = (COMBOBOX)m_comboBox.GetCurSel();

	switch (m_eLight)
	{
	case DlgLightTool::COMBOBOX::POINTLIGNT:
		break;
	case DlgLightTool::COMBOBOX::SPOTLIGNT:
		break;
	case DlgLightTool::COMBOBOX::DIRECTIONALLIGNT:
		break;
	default:
		break;
	}


	UpdateData(FALSE);

}	


