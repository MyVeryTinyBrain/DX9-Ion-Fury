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
	, m_nOpa(0)
	, m_comboBox(COMBOBOX::END)
	, m_LightName(_T(""))
	, m_ColorR(0.f)
	, m_ColorG(0.f)
	, m_ColorB(0.f)
	, m_ColorA(0.f)
	, m_PosX(0.f)
	, m_PosY(0.f)
	, m_PosZ(0.f)
	, m_Radius(0.f)
	, m_LTDirX(0)
	, m_LTDirY(0)
	, m_LTDirZ(0)
{

}

DlgLightTool::~DlgLightTool()
{
}

void DlgLightTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT_SLIDER, m_SliderCtrl_Transparency);
	DDX_Control(pDX, IDC_LT_COMBOBOX, m_LT_ComboBox);
	DDX_Text(pDX, IDC_LT_LIGHTNAME, m_LightName);
	DDX_Text(pDX, IDC_COLOR_R, m_ColorR);
	DDX_Text(pDX, IDC_COLOR_G, m_ColorG);
	DDX_Text(pDX, IDC_COLOR_B, m_ColorB);
	DDX_Text(pDX, IDC_COLOR_A, m_ColorA);
	DDX_Text(pDX, IDC_LT_POSX, m_PosX);
	DDX_Text(pDX, IDC_LT_POSY, m_PosY);
	DDX_Text(pDX, IDC_LT_POSZ, m_PosZ);
	DDX_Text(pDX, IDC_LT_RADIUS, m_Radius);
	DDX_Control(pDX, IDC_SLIDERCTRL_RAD, m_SliderCrtl_Radius);
	DDX_Control(pDX, IDC_SLDER_DIRX, m_SliderDirX);
	DDX_Control(pDX, IDC_SLDER_DIRY, m_SliderDirY);
	DDX_Control(pDX, IDC_SLDER_DIRZ, m_SliderDirZ);
	DDX_Text(pDX, IDC_LT_DIRX, m_LTDirX);
	DDX_Text(pDX, IDC_LT_DIRY, m_LTDirY);
	DDX_Text(pDX, IDC_LT_DIRZ, m_LTDirZ);
}


BEGIN_MESSAGE_MAP(DlgLightTool, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgLightTool::OnLightTool_ComboBox)
END_MESSAGE_MAP()


// DlgLightTool 메시지 처리기


BOOL DlgLightTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//LightTool 투명도 설정하기 위한 초기화 작업을 추가합니다.  
	m_SliderCtrl_Transparency.SetRange(30, 255);
	m_SliderCtrl_Transparency.SetPos(255);
	m_nOpa = m_SliderCtrl_Transparency.GetPos();
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	SetAttr(m_nOpa);

	//Type 콤보박스 추가 작업입니다. 
	m_LT_ComboBox.AddString(_T("Point"));
	m_LT_ComboBox.AddString(_T("Spot"));
	m_LT_ComboBox.AddString(_T("Directional"));
	m_LT_ComboBox.AddString(_T("Ambinent"));
	m_LT_ComboBox.SetCurSel(3);

	//반지름 슬라이드컨트롤 초기화 작업을 추가합니다. 
	m_SliderCrtl_Radius.SetRange(0, 50);       // 사용영역 값 설정한다.
	m_SliderCrtl_Radius.SetRangeMin(0);			//최소 값 설정
	m_SliderCrtl_Radius.SetRangeMax(50);		//최대 값 설정
	m_SliderCrtl_Radius.SetPos(10);				//위치 설정
	m_SliderCrtl_Radius.SetPageSize(0.1);		//눈금 간격 설정

	//방향 슬라이드컨트롤 초기화 작업을 추가합니다. 
	m_SliderDirX.SetRange(0, 300);
	m_SliderDirX.SetPos(0);
	m_SliderDirY.SetRange(0, 300);
	m_SliderDirY.SetPos(0);
	m_SliderDirZ.SetRange(0, 300);
	m_SliderDirZ.SetPos(0);





	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgLightTool::SetAttr(int iOpa)
{
	SetLayeredWindowAttributes(RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);
}



void DlgLightTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;

	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_LT_SLIDER:
		m_SliderCtrl_Transparency.SetPos(pSlider->GetPos());
		SetAttr(pSlider->GetPos());
		break;
	case IDC_SLIDERCTRL_RAD:
		m_SliderCrtl_Radius.SetPos(pSlider->GetPos());
		int iPos = m_SliderCrtl_Radius.GetPos();
		break;
	case IDC_SLDER_DIRX:
		m_SliderDirX.SetPos(pSlider->GetPos());
		break;
	case IDC_SLDER_DIRY:
		m_SliderDirY.SetPos(pSlider->GetPos());
		break;
	case IDC_SLDER_DIRZ:
		m_SliderDirZ.SetPos(pSlider->GetPos());
		break;
	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgLightTool::OnLightTool_ComboBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	UpdateData(FALSE);
}
