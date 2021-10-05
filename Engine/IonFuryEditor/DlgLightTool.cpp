// DlgLightTool.cpp: 구현 파일
//



#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgLightTool.h"
#include "afxdialogex.h"

//IDC_LT_COLORR
//m_ColorR

// DlgLightTool 대화 상자

IMPLEMENT_DYNAMIC(DlgLightTool, CDialog)

DlgLightTool::DlgLightTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgLightTool, pParent)
	, m_eLTComboBox(COMBOBOX::END)
	, m_ColorR(0.f)
	, m_ColorG(0.f)
	, m_ColorB(0.f)
	, m_ColorA(0.f)
	, m_PosX(0.f)
	, m_PosY(0.f)
	, m_PosZ(0.f)
	, m_Radius(0.f)
	, m_DirX(0.f)
	, m_DirY(0.f)
	, m_DirZ(0.f)
	, m_nOpa(0)
{

}

DlgLightTool::~DlgLightTool()
{
}

void DlgLightTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_LightToolComboBox);
	DDX_Text(pDX, IDC_LT_COLORR, m_ColorR);
	DDX_Text(pDX, IDC_LT_COLORG, m_ColorG);
	DDX_Text(pDX, IDC_LT_COLORB, m_ColorB);
	DDX_Text(pDX, IDC_LT_COLORA, m_ColorA);
	DDX_Text(pDX, IDC_LT_POSITIONX, m_PosX);
	DDX_Text(pDX, IDC_LT_POSITIONY, m_PosY);
	DDX_Text(pDX, IDC_LT_POSITIONZ, m_PosZ);
	DDX_Text(pDX, IDC_LT_RADIUS, m_Radius);
	DDX_Text(pDX, IDC_DIRECTIONX, m_DirX);
	DDX_Text(pDX, IDC_DIRECTIONY, m_DirY);
	DDX_Text(pDX, IDC_DIRECTIONZ, m_DirZ);
	DDX_Control(pDX, IDC_SLIDER1, m_TransparencyCtrl);
}


BEGIN_MESSAGE_MAP(DlgLightTool, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgLightTool::OnLightToolComboBox)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDCANCEL, &DlgLightTool::OnBnClickedCancel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &DlgLightTool::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// DlgLightTool 메시지 처리기


BOOL DlgLightTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_LightToolComboBox.AddString(_T("Point"));
	m_LightToolComboBox.AddString(_T("Spot"));
	m_LightToolComboBox.AddString(_T("Directional"));
	m_LightToolComboBox.AddString(_T("Ambinent"));
	m_LightToolComboBox.SetCurSel(3);


	//LightTool 투명도 설정하기 위한 초기화 작업을 추가합니다.  
	m_TransparencyCtrl.SetRange(30, 255);
	m_TransparencyCtrl.SetPos(150);
	m_nOpa = m_TransparencyCtrl.GetPos();
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	SetAttr(m_nOpa);


	//방향 슬라이드컨트롤 설정을 위한 초기화 작업을 추가합니다. 
	//m_




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgLightTool::SetAttr(int iOpa)
{
	SetLayeredWindowAttributes(RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);
}


void DlgLightTool::OnLightToolComboBox()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



BOOL DlgLightTool::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CRect rect;
	GetClientRect(rect);

	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}




void DlgLightTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;

	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_SLIDER1:
		m_TransparencyCtrl.SetPos(pSlider->GetPos());
		break;
	default:
		break;
	}

	SetAttr(pSlider->GetPos());


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgLightTool::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


void DlgLightTool::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
