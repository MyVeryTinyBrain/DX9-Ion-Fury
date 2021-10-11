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
	, m_dirx(0)
	, m_diry(0)
	, m_dirz(0)
	, sdirX(_T(""))
	, sdirY(_T(""))
	, sdirZ(_T(""))
	, m_ambinentFactor(0)
	, m_radius(0)
	, lightcom(nullptr)
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
	DDX_Text(pDX, IDC_LT_DIRX, m_dirx);
	DDX_Text(pDX, IDC_LT_DIRY, m_diry);
	DDX_Text(pDX, IDC_LT_DIRZ, m_dirz);
	DDX_Text(pDX, IDC_EDIT1, m_ambinentFactor);
	DDX_Text(pDX, IDC_LT_RADIUS, m_radius);
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
	ON_BN_CLICKED(IDC_BUTTON5, &DlgLightTool::OnBnClickedAmbinentFactorSet)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgLightTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON4, &DlgLightTool::OnBnClickedLoad)
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
	m_SliderCrtl_Radius.SetRange(0, 180.f);       // 사용영역 값 설정한다.
	m_SliderCrtl_Radius.SetPos(0.f);				//위치 설정
	m_SliderCrtl_Radius.SetLineSize(0.5f);		//방향키로 움질일 때 사이즈 
	m_SliderCrtl_Radius.SetPageSize(0.5f);		//눈금 간격 설정

	iPos = m_SliderCrtl_Radius.GetPos();
	sPos.Format(_T(" % d"), (float)iPos);
	m_Radius.SetWindowText(sPos);

	//방향 슬라이드컨트롤 초기화 작업을 추가합니다. 
	m_SliderDirX.SetRange(0, 360.f);
	m_SliderDirX.SetPos(0);
	m_SliderDirY.SetRange(0, 360.f);
	m_SliderDirY.SetPos(0);
	m_SliderDirZ.SetRange(0, 360.f);
	m_SliderDirZ.SetPos(0);

	iPosX = m_SliderDirX.GetPos();
	sPosX.Format(_T(" % d"), (float)iPosX);
	m_DirX.SetWindowText(sPosX);

	iPosY = m_SliderDirY.GetPos();
	sPosY.Format(_T(" % d"), (float)iPosY);
	m_DirY.SetWindowText(sPosY);

	iPosZ = m_SliderDirX.GetPos();
	sPosZ.Format(_T(" % d"), (float)iPosZ);
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
	if (iIndex < 0)
		return;
	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);


	CString name = wstrFindName.GetString();

	LightObj::LightPick(name);

	if (m_LightType == L"Point" || m_LightType == L"Spot")
	{

		for (auto& light : LightObj::g_vecLight)
		{

			auto lightobj = light->GetGameObject();

			if (lightobj->name == name.GetString())
			{

				if (lightobj->tag == L"Point")
				{
					auto com = lightobj->GetComponentInChild<PointLight>();

					m_LightType = lightobj->tag.c_str();
					m_LightName = lightobj->GetName().c_str();

					m_ColorR = com->GetColor().r;
					m_ColorG = com->GetColor().g;
					m_ColorB = com->GetColor().b;
					m_ColorA = com->GetColor().a;

					m_PosX = lightobj->GetTransform()->position.x;
					m_PosY = lightobj->GetTransform()->position.y;
					m_PosZ = lightobj->GetTransform()->position.z;

					m_radius = com->range;

					m_dirx = lightobj->GetTransform()->rotation.x;
					m_diry = lightobj->GetTransform()->rotation.y;
					m_dirz = lightobj->GetTransform()->rotation.z;
					//m_Radius.SetWindowText();

				}
				else if (lightobj->tag == L"Spot")
				{
					auto com = lightobj->GetComponentInChild<SpotLight>();

					m_LightType = lightobj->tag.c_str();
					m_LightName = lightobj->GetName().c_str();

					m_ColorR = com->GetColor().r;
					m_ColorG = com->GetColor().g;
					m_ColorB = com->GetColor().b;
					m_ColorA = com->GetColor().a;

					m_PosX = lightobj->GetTransform()->position.x;
					m_PosY = lightobj->GetTransform()->position.y;
					m_PosZ = lightobj->GetTransform()->position.z;

					m_radius = com->range;

					m_dirx = lightobj->GetTransform()->rotation.x;
					m_diry = lightobj->GetTransform()->rotation.y;
					m_dirz = lightobj->GetTransform()->rotation.z;
				}
			}

		}
	}
	if (m_LightType == L"Directional")
	{
		auto directionallight = SceneManager::GetInstance()->GetCurrentScene()->FindGameObject(L"directionalLight");
		auto light = directionallight->GetComponent<DirectionalLight>();
		m_LightName = light->GetName().c_str();

		m_LightType = L"Directional";

		m_ColorR = light->GetColor().r;
		m_ColorG = light->GetColor().g;
		m_ColorB = light->GetColor().b;
		m_ColorA = light->GetColor().a;

		m_PosX = directionallight->GetTransform()->position.x;
		m_PosY = directionallight->GetTransform()->position.y;
		m_PosZ = directionallight->GetTransform()->position.z;

		m_dirz = directionallight->GetTransform()->rotation.z;
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
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void DlgLightTool::OnEnChangeLtRadius()
{
	//범위 반지름 슬라이더 조정


	int iIndex = m_LT_ListBox.GetCurSel();
	if (iIndex < 0)
		return;
	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);



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
				com->range = (float)iPos;
			}
			if (lightobj->tag == L"Spot")
			{
				auto com = lightobj->GetComponentInChild<SpotLight>();
				com->range = (float)iPos;
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
	//방향 Z 축 슬라이더 에디터박스 조정
	m_DirZ.GetWindowText(sPosZ);
	iPosZ = _ttoi(sPosZ);

	int iIndex = m_LT_ListBox.GetCurSel();

	if (iIndex < 0)
		return;

	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);

	CString name = wstrFindName.GetString();

	m_SliderDirZ.SetPos(iPosZ);

	if (m_LightType == L"Point" || m_LightType == L"Spot")
	{

		for (auto& light : LightObj::g_vecLight)
		{
			auto lightobj = light->GetGameObject();

			if (lightobj->name == name.GetString())
			{
				if (lightobj->tag == L"Point")
				{
					auto com = lightobj->GetComponentInChild<PointLight>();
					m_DirX.GetWindowText(sdirX);
					m_dirx = (float)_ttoi(sdirX);

					m_DirY.GetWindowText(sdirY);
					m_diry = (float)_ttoi(sdirY);

					m_DirZ.GetWindowText(sdirZ);
					m_dirz = (float)_ttoi(sdirZ);

					com->transform->rotation = Quat::FromEuler(m_dirx, m_diry, m_dirz);
				}
				else if (lightobj->tag == L"Spot")
				{
					auto com = lightobj->GetComponentInChild<SpotLight>();
					m_DirX.GetWindowText(sdirX);
					m_dirx = (float)_ttoi(sdirX);

					m_DirY.GetWindowText(sdirY);
					m_diry = (float)_ttoi(sdirY);

					m_DirZ.GetWindowText(sdirZ);
					m_dirz = (float)_ttoi(sdirZ);
					com->transform->rotation = Quat::FromEuler(m_dirx, m_diry, m_dirz);
				}

				break;
			}
		}
	}

	else if (m_LightType == L"Directional")
	{
		auto directionallight = SceneManager::GetInstance()->GetCurrentScene()->FindGameObject(L"directionalLight");
		auto light = directionallight->GetComponent<DirectionalLight>();
		//m_DirX.GetWindowText(sdirX);
		//m_dirx = (float)_ttoi(sdirX);

		//m_DirY.GetWindowText(sdirY);
		//m_diry = (float)_ttoi(sdirY);

		m_DirZ.GetWindowText(sdirZ);
		m_dirz = (float)_ttoi(sdirZ);
		light->transform->rotation = Quat::FromEuler(m_dirx, m_diry, m_dirz);
	}

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
	if (iIndex < 0)
		return;

	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);


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

	if (iIndex < 0)
		return;

	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);

	CString name = wstrFindName.GetString();

	if (m_LightType == L"Point" || m_LightType == L"Spot")
	{

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
				else if (lightobj->tag == L"Spot")
				{
					auto com = lightobj->GetComponentInChild<SpotLight>();
					com->color = Vec4(m_ColorR, m_ColorG, m_ColorB, m_ColorA);
				}

				m_DirX.GetWindowText(sdirX);
				m_dirx = (float)_ttoi(sdirX);

				m_DirY.GetWindowText(sdirY);
				m_diry = (float)_ttoi(sdirY);

				m_DirZ.GetWindowText(sdirZ);
				m_dirz = (float)_ttoi(sdirZ);

				lightobj->transform->position = Vec3(m_PosX, m_PosY, m_PosZ);
				lightobj->transform->rotation = Quat::FromEuler(m_dirx, m_diry, m_dirz);

				break;
			}
		}
	}

	if (m_LightType == L"Directional")
	{
		auto directionallight = SceneManager::GetInstance()->GetCurrentScene()->FindGameObject(L"directionalLight");
		auto light = directionallight->GetComponent<DirectionalLight>();
		light->color = Vec4(m_ColorR, m_ColorG, m_ColorB, m_ColorA);

		m_DirX.GetWindowText(sdirX);
		m_dirx = (float)_ttoi(sdirX);

		m_DirY.GetWindowText(sdirY);
		m_diry = (float)_ttoi(sdirY);

		m_DirZ.GetWindowText(sdirZ);
		m_dirz = (float)_ttoi(sdirZ);

		light->transform->rotation = Quat::FromEuler(m_dirx, m_diry, m_dirz);
	}

	UpdateData(FALSE);

}


void DlgLightTool::OnBnClickedAddButton()
{
	UpdateData(TRUE);
	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();


	for (auto& light : LightObj::g_vecLight)
	{
		auto lightobj = light->GetGameObject();

		if (lightobj->name == m_LightName.GetString())
		{
			return;
		}
	}

	CString temp = m_LightType.GetString();

	if (m_LightType == L"Point")
	{
		GameObject* PointLightObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(m_LightType.GetString());

		PointLightObj->name = m_LightName.GetString();

		PointLightObj->transform->position = Vec3(m_PosX, m_PosY, m_PosZ);

		//PointLightObj->transform->position = camera->GetGameObject()->transform->position + camera->GetGameObject()->transform->forward * 2;

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


void DlgLightTool::OnBnClickedAmbinentFactorSet()
{
	UpdateData(TRUE);

	//lightcom->SetAmbientFactor(m_ambinentFactor);
	////어떤라이트에세팅해줄건지 


	int iIndex = m_LT_ListBox.GetCurSel();

	if (iIndex < 0)
		return;

	CString wstrFindName;
	m_LT_ListBox.GetText(iIndex, wstrFindName);

	CString name = wstrFindName.GetString();

	if (m_LightType == L"Point" || m_LightType == L"Spot")
	{

		for (auto& light : LightObj::g_vecLight)
		{
			auto lightobj = light->GetGameObject();

			if (lightobj->name == name.GetString())
			{
				if (lightobj->tag == L"Point")
				{
					auto com = lightobj->GetComponentInChild<PointLight>();
					com->SetAmbientFactor(m_ambinentFactor);
				}
				else if (lightobj->tag == L"Spot")
				{
					auto com = lightobj->GetComponentInChild<SpotLight>();
					com->SetAmbientFactor(m_ambinentFactor);
				}

				break;
			}
		}
	}

	else if (m_LightType == L"Directional")
	{
		auto directionallight = SceneManager::GetInstance()->GetCurrentScene()->FindGameObject(L"directionalLight");
		auto light = directionallight->GetComponent<DirectionalLight>();
		light->SetAmbientFactor(m_ambinentFactor);
	}

	UpdateData(FALSE);
}


void DlgLightTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		DWORD dwStrByte2 = 0;
		DWORD dwStrByte3 = 0;
		DWORD dwStrByte4 = 0;
		CString strMesh = L"";
		CString tex = L"";
		float range = 0.f;
		float ambinentfactor = 0.f;


		auto lightObj = LightObj::g_vecLight;


		for (auto& light : lightObj)
		{
			auto obj = light->GetGameObject();

			dwStrByte = sizeof(wchar_t) * (obj->name.length() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, obj->name.c_str(), dwStrByte, &dwByte, nullptr);				// 이름


			dwStrByte2 = sizeof(wchar_t) * (obj->tag.length() + 1);
			WriteFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, obj->tag.c_str(), dwStrByte2, &dwByte, nullptr);				// tag

			WriteFile(hFile, &obj->transform->position, sizeof(Vec3), &dwByte, nullptr);	// pos
			WriteFile(hFile, &obj->transform->rotation, sizeof(Vec3), &dwByte, nullptr);	// rotation


			if (obj->tag.c_str() == L"Point")
			{
				auto point = obj->GetComponent<PointLight>();

				ambinentfactor = point->ambientFactor;
				WriteFile(hFile, &ambinentfactor, sizeof(float), &dwByte, nullptr);				// ambinentfactor

				range = point->range;
				WriteFile(hFile, &point->color, sizeof(Vec4), &dwByte, nullptr);			// color
				WriteFile(hFile, &range, sizeof(float), &dwByte, nullptr);					// range

			}
			else if (obj->tag.c_str() == L"Spot")
			{
				auto point = obj->GetComponent<SpotLight>();

				ambinentfactor = point->ambientFactor;
				WriteFile(hFile, &ambinentfactor, sizeof(float), &dwByte, nullptr);				// ambinentfactor

				range = point->range;
				WriteFile(hFile, &point->color, sizeof(Vec4), &dwByte, nullptr);			// color
				WriteFile(hFile, &range, sizeof(float), &dwByte, nullptr);					// range

			}
			else if (obj->tag.c_str() == L"Directional")
			{
				auto point = obj->GetComponent<DirectionalLight>();

				ambinentfactor = point->ambientFactor;
				WriteFile(hFile, &ambinentfactor, sizeof(float), &dwByte, nullptr);				// ambinentfactor

				WriteFile(hFile, &point->color, sizeof(Vec4), &dwByte, nullptr);			// color
			}

		}

		CloseHandle(hFile);
	}
}


void DlgLightTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH]{};

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		// Release
		int vecSize = LightObj::g_vecLight.size();
		for (int i = 0; i < vecSize; ++i)
		{
			LightObj::g_vecLight[0]->gameObject->Destroy();
		}
		//

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		DWORD dwStrByte2 = 0;
		DWORD dwStrByte3 = 0;
		DWORD dwStrByte4 = 0;

		wchar_t* pBuff = nullptr;
		wchar_t* pBuff2 = nullptr;
		wchar_t* pBuff3 = nullptr;
		wchar_t* pBuff4 = nullptr;

		GameObject* pObj = nullptr;
		Vec3 vPos = {};
		Vec3 vScale = {};
		Vec3 vRot = {};
		float frange = 0.f;
		Vec4 Vcolor = {};
		float fambinentfactor = 0.f;
		CString tag = {};


		while (true)
		{
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);		// 이름
			pBuff = new wchar_t[dwStrByte];
			ReadFile(hFile, pBuff, dwStrByte, &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);		// tag
			pBuff2 = new wchar_t[dwStrByte2];
			ReadFile(hFile, pBuff2, dwStrByte2, &dwByte, nullptr);
			tag = pBuff2;

			if (0 == dwByte)
			{
				SafeDeleteArray(pBuff);
				SafeDeleteArray(pBuff2);
				break;
			}

			pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(pBuff2);
			pObj->name = pBuff;

			LightObj* lightobj = pObj->AddComponent<LightObj>();

			SafeDeleteArray(pBuff);
			SafeDeleteArray(pBuff2);

			ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);				// pos
			ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);				// rotation
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);	// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);			// color
			ReadFile(hFile, &frange, sizeof(float), &dwByte, nullptr);			// range

			pObj->transform->position = vPos;
			pObj->transform->rotation = Quat::FromEuler(vRot.x, vRot.y, vRot.z);


			if (tag == L"Spot")
			{
				auto spot = pObj->GetComponent<SpotLight>();
				spot->range = frange;
				spot->ambientFactor = fambinentfactor;
				spot->color = Vcolor;

			}
			else if (tag == L"Point")
			{
				auto point = pObj->GetComponent<PointLight>();
				point->range = frange;
				point->ambientFactor = fambinentfactor;
				point->color = Vcolor;

			}
			else
			{
				auto directional = pObj->GetComponent<DirectionalLight>();
				directional->ambientFactor = fambinentfactor;
				directional->color = Vcolor;
			}


		}

		CloseHandle(hFile);
	}

}
