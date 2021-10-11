// DlgLightTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgLightTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "LightObj.h"

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
	, iPos(0)
	, m_LightType(_T(""))
	, sPos(_T(""))
	, sPosX(_T(""))
	, sPosY(_T(""))
	, sPosZ(_T(""))
	, iPosX(0)
	, iPosY(0)
	, iPosZ(0)
	, m_OutSideAngle(0)
	, m_InsideAngleRatio(0)
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

	DDX_Control(pDX, IDC_SLIDERCTRL_RAD, m_SliderCrtl_Radius);
	DDX_Control(pDX, IDC_LT_RADIUS, m_Radius);

	DDX_Control(pDX, IDC_SLDER_DIRX, m_SliderDirX);
	DDX_Control(pDX, IDC_SLDER_DIRY, m_SliderDirY);
	DDX_Control(pDX, IDC_SLDER_DIRZ, m_SliderDirZ);
	DDX_Control(pDX, IDC_LIST1, m_LT_ListBox);
	DDX_CBString(pDX, IDC_LT_COMBOBOX, m_LightType);

	DDX_Control(pDX, IDC_LT_DIRX, m_DirX);
	DDX_Control(pDX, IDC_LT_DIRY, m_DirY);
	DDX_Control(pDX, IDC_LT_DIRZ, m_DirZ);
	DDX_Text(pDX, IDC_EDIT2, m_OutSideAngle);
	DDX_Text(pDX, IDC_EDIT3, m_InsideAngleRatio);
}


BEGIN_MESSAGE_MAP(DlgLightTool, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgLightTool::OnListBoxCtrl)
	ON_CBN_SELCHANGE(IDC_LT_COMBOBOX, &DlgLightTool::OnSelectLight)
	ON_EN_CHANGE(IDC_LT_LIGHTNAME, &DlgLightTool::OnLightName)
	ON_EN_CHANGE(IDC_LT_RADIUS, &DlgLightTool::OnEnChangeLtRadius)
	ON_EN_CHANGE(IDC_LT_DIRX, &DlgLightTool::OnEnChangeLtDirx)
	ON_EN_CHANGE(IDC_LT_DIRY, &DlgLightTool::OnEnChangeLtDiry)
	ON_EN_CHANGE(IDC_LT_DIRZ, &DlgLightTool::OnEnChangeLtDirz)
	ON_EN_CHANGE(IDC_COLOR_R, &DlgLightTool::OnEnChangeColorR)
	ON_EN_CHANGE(IDC_COLOR_G, &DlgLightTool::OnEnChangeColorG)
	ON_EN_CHANGE(IDC_COLOR_B, &DlgLightTool::OnEnChangeColorB)
	ON_EN_CHANGE(IDC_COLOR_A, &DlgLightTool::OnEnChangeColorA)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgLightTool::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgLightTool::OnBnClickedApplyButton)
	ON_BN_CLICKED(IDC_BUTTON6, &DlgLightTool::OnBnClickedAddButton)
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
	//m_LT_ComboBox.AddString(_T("Ambinent"));
	m_LT_ComboBox.SetCurSel(0);
	//m_LightType = L"Point";

	//반지름 슬라이드컨트롤 초기화 작업을 추가합니다. 
	m_SliderCrtl_Radius.SetRange(0, 180);       // 사용영역 값 설정한다.
	m_SliderCrtl_Radius.SetPos(0);				//위치 설정
	m_SliderCrtl_Radius.SetLineSize(1);		//방향키로 움질일 때 사이즈 
	m_SliderCrtl_Radius.SetPageSize(1);		//눈금 간격 설정

	iPos = m_SliderCrtl_Radius.GetPos();
	sPos.Format(_T(" % d"), iPos);
	m_Radius.SetWindowText(sPos);

	//방향 슬라이드컨트롤 초기화 작업을 추가합니다. 
	m_SliderDirX.SetRange(0, 360);
	m_SliderDirX.SetPos(0);
	m_SliderDirY.SetRange(0, 360);
	m_SliderDirY.SetPos(0);
	m_SliderDirZ.SetRange(0, 360);
	m_SliderDirZ.SetPos(0);

	iPosX = m_SliderDirX.GetPos();
	sPosX.Format(_T(" % d"), iPosX);
	m_DirX.SetWindowText(sPosX);

	iPosY = m_SliderDirY.GetPos();
	sPosY.Format(_T(" % d"), iPosY);
	m_DirY.SetWindowText(sPosY);

	iPosZ = m_SliderDirX.GetPos();
	sPosZ.Format(_T(" % d"), iPosZ);
	m_DirZ.SetWindowText(sPosZ);



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
		iPos = m_SliderCrtl_Radius.GetPos();
		sPos.Format(_T("%d"), iPos);
		m_Radius.SetWindowText(sPos);
		break;
	case IDC_SLDER_DIRX:
		m_SliderDirX.SetPos(pSlider->GetPos());
		iPosX = m_SliderDirX.GetPos();
		sPosX.Format(_T("%d"), iPosX);
		m_DirX.SetWindowText(sPosX);
		break;
	case IDC_SLDER_DIRY:
		m_SliderDirY.SetPos(pSlider->GetPos());
		iPosY = m_SliderDirY.GetPos();
		sPosY.Format(_T("%d"), iPosY);
		m_DirY.SetWindowText(sPosY);
		break;
	case IDC_SLDER_DIRZ:
		m_SliderDirZ.SetPos(pSlider->GetPos());
		iPosZ = m_SliderDirZ.GetPos();
		sPosZ.Format(_T("%d"), iPosZ);
		m_DirZ.SetWindowText(sPosZ);
		break;
	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


//조명 리스트 박스 컨트럴
void DlgLightTool::SetListBox(const wstring& lightObjName)
{
	UpdateData(TRUE);

	m_LT_ListBox.AddString(lightObjName.c_str());

	UpdateData(FALSE);
}

void DlgLightTool::OnListBoxCtrl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iIndex = m_LT_ListBox.GetCurSel();
	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);


	if (iIndex < 0)
		return;

	CString name = wstrFindName.GetString();

	for (auto& light : LightObj::g_vecLight)
	{

		auto lightobj = light->GetGameObject();

		if (lightobj->name == name.GetString())
		{
			if (lightobj->tag == L"Point")
			{
				auto com = lightobj->GetComponentInChild<PointLight>();

				//com->color = Vec4(m_ColorR, m_ColorG, m_ColorB, m_ColorA);
			}
			else if (lightobj->tag == L"Spot")
			{
				auto com = lightobj->GetComponentInChild<SpotLight>();

				//com->color = Vec4(m_ColorR, m_ColorG, m_ColorB, m_ColorA);
			}
			// 불러올때 LightObj에서 이름을 가져오면 될듯
		}

	}


	UpdateData(FALSE);
}


//조명 선택
void DlgLightTool::OnSelectLight()
{
	UpdateData(TRUE);

	m_comboBox = (COMBOBOX)m_LT_ComboBox.GetCurSel(); //선택한거

	switch (m_comboBox)
	{
	case DlgLightTool::COMBOBOX::POINTLIGNT:
		m_LightType = L"Point";
		break;
	case DlgLightTool::COMBOBOX::SPOTLIGNT:
		m_LightType = L"Spot";
		break;
	case DlgLightTool::COMBOBOX::DIRECTIONALLIGNT:
		m_LightType = L"Directional";
		break;
	case DlgLightTool::COMBOBOX::AMBINENTLIGHT:
		m_LightType = L"Ambinent";
		break;
	default:
		break;
	}


	UpdateData(FALSE);
}


void DlgLightTool::OnLightName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);



	UpdateData(FALSE);

}


void DlgLightTool::OnEnChangeLtRadius()
{
	//범위 반지름 슬라이더 조정


	int iIndex = m_LT_ListBox.GetCurSel();
	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);


	if (iIndex < 0)
		return;

	m_LT_ListBox.GetText(iIndex, wstrFindName);

	CString name = wstrFindName.GetString();

	m_Radius.GetWindowText(sPos);
	iPos = _ttoi(sPos);

	m_SliderCrtl_Radius.SetPos(iPos);

	for (auto& light : LightObj::g_vecLight)
	{
		auto lightobj = light->GetGameObject();

		if (lightobj->name == name.GetString())
		{
			if (lightobj->tag == L"Point")
			{
				auto com = lightobj->GetComponentInChild<PointLight>();
				com->range = iPos;
			}
			else
			{
				auto com = lightobj->GetComponentInChild<SpotLight>();
				com->range = iPos;
			}

			break;
		}
	}
}


void DlgLightTool::OnEnChangeLtDirx()
{
	//방향 X 축 슬라이더 에디터박스 조정
	m_DirX.GetWindowText(sPosX);
	iPosX = _ttoi(sPosX);

	m_SliderDirX.SetPos(iPosX);
}


void DlgLightTool::OnEnChangeLtDiry()
{
	//방향 X 축 슬라이더 에디터박스 조정
	m_DirY.GetWindowText(sPosY);
	iPosY = _ttoi(sPosY);

	m_SliderDirY.SetPos(iPosY);
}


void DlgLightTool::OnEnChangeLtDirz()
{
	//방향 X 축 슬라이더 에디터박스 조정
	m_DirZ.GetWindowText(sPosZ);
	iPosZ = _ttoi(sPosZ);

	m_SliderDirZ.SetPos(iPosZ);
}


void DlgLightTool::OnEnChangeColorR()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void DlgLightTool::OnEnChangeColorG()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void DlgLightTool::OnEnChangeColorB()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void DlgLightTool::OnEnChangeColorA()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void DlgLightTool::OnBnClickedDeleteButton()
{
	UpdateData(TRUE);

	int iIndex = m_LT_ListBox.GetCurSel();
	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);


	if (iIndex < 0)
		return;

	CString name = wstrFindName.GetString();

	for (auto& light : LightObj::g_vecLight)
	{

		auto lightobj = light->GetGameObject();

		auto test = lightobj->GetComponent<LightObj>();


		if (lightobj->name == name.GetString())
		{
			light->RequireDestroy();
			break;
		}
	}


	m_LT_ListBox.DeleteString(iIndex);
	UpdateData(FALSE);
}


void DlgLightTool::OnBnClickedApplyButton()
{
	UpdateData(TRUE);

	int iIndex = m_LT_ListBox.GetCurSel();
	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);


	if (iIndex < 0)
		return;

	m_LT_ListBox.GetText(iIndex, wstrFindName);

	CString name = wstrFindName.GetString();

	for (auto& light : LightObj::g_vecLight)
	{
		auto lightobj = light->GetGameObject();

		if (lightobj->name == name.GetString())
		{
			if (lightobj->tag == L"Point")
			{
				auto com = lightobj->GetComponentInChild<PointLight>();
				com->color = Vec4(m_ColorR, m_ColorG, m_ColorB, m_ColorA);
			}
			else
			{
				auto com = lightobj->GetComponentInChild<SpotLight>();
				com->color = Vec4(m_ColorR, m_ColorG, m_ColorB, m_ColorA);
			}
			lightobj->transform->position = Vec3(m_PosX, m_PosY, m_PosZ);

			break;
		}
	}

	
	UpdateData(FALSE);

}


void DlgLightTool::OnBnClickedAddButton()
{
	UpdateData(TRUE);
	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();


	CString temp = m_LightType.GetString();

	if(m_LightType == L"Point")
	{
		GameObject* PointLightObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(m_LightType.GetString());

		PointLightObj->name = m_LightName.GetString();

		//PointLightObj->transform->position = Vec3(m_PosX, m_PosY, m_PosZ);

		PointLightObj->transform->position = camera->GetGameObject()->transform->position + camera->GetGameObject()->transform->forward * 2;

		PointLightObj->AddComponent<LightObj>();

		m_LT_ListBox.AddString(m_LightName.GetString());
	}
	else if (m_LightType == L"Spot")
	{
		GameObject* SpotLightObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(m_LightType.GetString());

		SpotLightObj->name = m_LightName.GetString();

		SpotLightObj->transform->position = Vec3(m_PosX, m_PosY, m_PosZ);

		SpotLightObj->AddComponent<LightObj>();

		m_LT_ListBox.AddString(m_LightName.GetString());
	}

	UpdateData(FALSE);
}
