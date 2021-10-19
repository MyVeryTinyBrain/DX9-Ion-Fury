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
	DDX_Control(pDX, IDC_SLIDER2, m_SliderScaleX);
	DDX_Control(pDX, IDC_SLIDER4, m_SliderScaleY);
	DDX_Control(pDX, IDC_SLIDER5, m_SliderScaleZ);
	DDX_Control(pDX, IDC_SLIDER3, m_SliderRotationX);
	DDX_Control(pDX, IDC_SLIDER6, m_SliderRotationY);
	DDX_Control(pDX, IDC_SLIDER11, m_SliderRotationZ);
	DDX_Control(pDX, IDC_SLIDER1, m_PivotSliderScale);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Control(pDX, IDC_COMBO1, m_TypeComboBox);
}

// DlgObjectTool 메시지 처리기

BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON17, &DlgObjectTool::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_BUTTON18, &DlgObjectTool::OnBnClickedResetType)
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgObjectTool::OnLbnSelchangeListBox)
END_MESSAGE_MAP()


void DlgObjectTool::SetScaleScrollToDefault(HandlingObject* picked)
{
	m_SliderScaleX.SetPos(20);
	m_SliderScaleY.SetPos(20);
	m_SliderScaleZ.SetPos(20);

	m_PivotSliderScale.SetPos(20);

	if (picked == nullptr)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->GetSelectedObject()->transform->SetScale(Vec3(1.f, 1.f, 1.f));
}


void DlgObjectTool::SetRotationScrollToDefault(HandlingObject* picked)
{
	m_SliderRotationX.SetPos(180);
	m_SliderRotationY.SetPos(180);
	m_SliderRotationZ.SetPos(180);

	if (picked == nullptr)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->GetSelectedObject()->transform->SetEulerAngle(Vec3(0.f, 0.f, 0.f));
}


void DlgObjectTool::SetScaleScrollToPicked(HandlingObject* picked)
{
	Transform* PivotTransform = picked->GetPivotObject()->GetTransform();
	Transform* ChildTransform = picked->GetChildObject()->GetTransform();
	
	Vec3 Scale = ChildTransform->scale;
	float ScaleX = Scale.x * 20.f;
	float ScaleY = Scale.y * 20.f;
	float ScaleZ = Scale.z * 20.f;
	m_SliderScaleX.SetPos((int)ScaleX);
	m_SliderScaleY.SetPos((int)ScaleY);
	m_SliderScaleZ.SetPos((int)ScaleZ);

	Scale = PivotTransform->scale;
	m_PivotSliderScale.SetPos((int)(Scale.x * 20));
}


void DlgObjectTool::SetRotationScrollToPicked(HandlingObject* picked)
{
	Transform* ParentTransform = picked->GetGameObject()->GetTransform();

	Vec3 EulerAngle = ParentTransform->GetEulerAngle();

	float RotationX = EulerAngle.x + 180;
	float RotationY = EulerAngle.y + 180;
	float RotationZ = EulerAngle.z + 180;

	m_SliderRotationX.SetPos((int)RotationX);
	m_SliderRotationY.SetPos((int)RotationY);
	m_SliderRotationZ.SetPos((int)RotationZ);
}


BOOL DlgObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	{
		m_TypeComboBox.AddString(_T("ItemBowAmmo"));
		m_TypeComboBox.AddString(_T("ItemChaingunAmmo"));
		m_TypeComboBox.AddString(_T("ItemLauncherAmmo"));
		m_TypeComboBox.AddString(_T("ItemRevolverAmmo"));
		m_TypeComboBox.AddString(_T("ItemShotgunAmmo"));
		m_TypeComboBox.AddString(_T("ItemSMGAmmo"));
		m_TypeComboBox.AddString(_T("ItemHealthPack"));
	}

	{	//RotSlider 설정
		m_SliderRotationX.SetRange(0, 360);
		m_SliderRotationX.SetPos(180);
		m_SliderRotationX.SetLineSize(10);

		m_SliderRotationY.SetRange(0, 360);
		m_SliderRotationY.SetPos(180);
		m_SliderRotationY.SetLineSize(10);

		m_SliderRotationZ.SetRange(0, 360);
		m_SliderRotationZ.SetPos(180);
		m_SliderRotationZ.SetLineSize(10);
	}

	{	//ScaleSlider 설정
		m_SliderScaleX.SetRange(0, 100);
		m_SliderScaleX.SetPos(20);
		m_SliderScaleX.SetLineSize(10);

		m_SliderScaleY.SetRange(0, 100);
		m_SliderScaleY.SetPos(20);
		m_SliderScaleY.SetLineSize(10);

		m_SliderScaleZ.SetRange(0, 100);
		m_SliderScaleZ.SetPos(20);
		m_SliderScaleZ.SetLineSize(10);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgObjectTool::OnBnClickedAddButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_TypeComboBox.GetCurSel() == -1)
		return;

	HandlingObject* Obj = EditorManager::GetInstance()->GetPerspectiveCamera()->Add_HandlingObject(m_Cnt);
	++m_Cnt;
	
	UpdateData(true);
	if (m_Name != L"")
		Obj->GetGameObject()->name = m_Name.GetString();

	CString Type = L"";
	m_TypeComboBox.GetLBText(m_TypeComboBox.GetCurSel(), Type);
	Obj->AddComponentToChildObject(Type);

	wstring name = Obj->GetGameObject()->name;
	m_ObjectListBox.AddString(name.c_str());

	int i = m_ObjectListBox.GetCount();
	m_ObjectListBox.SetCurSel(i - 1);
	
	m_Name = L"";
	m_TypeComboBox.SetCurSel(-1);
	SetScaleScrollToDefault();
	SetRotationScrollToDefault();

	UpdateData(false);
}


void DlgObjectTool::OnBnClickedResetType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TypeSelect = m_TypeComboBox.GetCurSel();
	if (TypeSelect == -1)
		return;

	int ObjSelect = m_ObjectListBox.GetCurSel();
	if (ObjSelect == -1)
		return;

	Transform* SelectedTransform = EditorManager::GetInstance()->GetGizmo()->GetSelectedObject();
	if (SelectedTransform == nullptr)
		return;
	if (SelectedTransform->GetGameObject()->GetComponent<HandlingObject>() == nullptr)
		return;

	HandlingObject* Obj = HandlingObject::g_HandlingVec[ObjSelect];

	CString Type = L"";
	m_TypeComboBox.GetLBText(TypeSelect, Type);
	Obj->RemoveChildObjectAndComponent();
	Obj->AddComponentToChildObject(Type);

	SetRotationScrollToDefault();
	SetScaleScrollToDefault();
}


void DlgObjectTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (!trans)
		return;

	HandlingObject* Picked = trans->GetGameObject()->GetComponent<HandlingObject>();

	if (!Picked)
		return;

	float ScaleX = float(m_SliderScaleX.GetPos() / 20.f);
	float ScaleY = float(m_SliderScaleY.GetPos() / 20.f);
	float ScaleZ = float(m_SliderScaleZ.GetPos() / 20.f);
	Picked->GetChildObject()->transform->scale = Vec3(ScaleX, ScaleY, ScaleZ);				//CompObj Scale
	
	float PivotScale = float(m_PivotSliderScale.GetPos() / 20.f);
	Picked->GetPivotObject()->transform->scale = Vec3(PivotScale, PivotScale, PivotScale);	//Pivot Scale

	float RotateX = float(m_SliderRotationX.GetPos() - 180);
	float RotateY = float(m_SliderRotationY.GetPos() - 180);
	float RotateZ = float(m_SliderRotationZ.GetPos() - 180);
	Picked->GetGameObject()->transform->SetEulerAngle(Vec3(RotateX, RotateY, RotateZ));		//Parent Rotation

	UpdateData(FALSE);

}


void DlgObjectTool::OnLbnSelchangeListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Select = m_ObjectListBox.GetCurSel();
	if (Select == -1)
		return;

	HandlingObject* Obj = HandlingObject::g_HandlingVec[Select];

	int ComponentSelect = -1;
	CString CompType = Obj->GetComponentType();
	ComponentSelect = m_TypeComboBox.FindStringExact(-1, CompType);
	m_TypeComboBox.SetCurSel(ComponentSelect);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	giz->Attach(Obj->transform);

	//ScaleRot picked값으로 scroll 변경
	SetScaleScrollToPicked(Obj);
	SetRotationScrollToPicked(Obj);
}
