// DlgMonsterTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgMonsterTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorEnum.h"

// DlgMonsterTool 대화 상자

IMPLEMENT_DYNAMIC(DlgMonsterTool, CDialog)

DlgMonsterTool::DlgMonsterTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgMonsterTool, pParent)
	, m_ChangingName(_T(""))
{

}

DlgMonsterTool::~DlgMonsterTool()
{
}

void DlgMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TriggerListBox);
	DDX_Control(pDX, IDC_LIST2, m_EventListBox);
	DDX_Control(pDX, IDC_RADIO2, m_TouchButtonManual1);
	DDX_Control(pDX, IDC_RADIO3, m_TouchButtonManual2);
	DDX_Control(pDX, IDC_RADIO4, m_TouchButtonManual3);
	DDX_Control(pDX, IDC_COMBO1, m_EventTypeComboBox);
	DDX_Control(pDX, IDC_SLIDER8, m_SliderScaleX);
	DDX_Control(pDX, IDC_SLIDER9, m_SliderScaleY);
	DDX_Control(pDX, IDC_SLIDER10, m_SliderScaleZ);
	DDX_Control(pDX, IDC_SLIDER2, m_SliderRotationX);
	DDX_Control(pDX, IDC_SLIDER4, m_SliderRotationY);
	DDX_Control(pDX, IDC_SLIDER7, m_SliderRotationZ);
	DDX_Text(pDX, IDC_EDIT1, m_ChangingName);
}


BEGIN_MESSAGE_MAP(DlgMonsterTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgMonsterTool::ClickAddTrigger)
	ON_BN_CLICKED(IDC_BUTTON8, &DlgMonsterTool::ClickRemoveTrigger)
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgMonsterTool::OnLbnSelChangeTrigger)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgMonsterTool::ClickAddEvent)
	ON_BN_CLICKED(IDC_BUTTON9, &DlgMonsterTool::ClickRemoveEvent)
	ON_LBN_SELCHANGE(IDC_LIST2, &DlgMonsterTool::OnLbnSelChangeEvent)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON5, &DlgMonsterTool::OnClickedTriggerMethodApply)
	ON_BN_CLICKED(IDC_BUTTON13, &DlgMonsterTool::OnClickedEventTypeApply)
	ON_BN_CLICKED(IDC_BUTTON14, &DlgMonsterTool::OnBnClickedChangeTriggerName)
	ON_BN_CLICKED(IDC_BUTTON15, &DlgMonsterTool::OnBnClickedChangeEventName)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgMonsterTool::OnBnClickedResetScale)
	ON_BN_CLICKED(IDC_BUTTON10, &DlgMonsterTool::OnBnClickedResetRotation)
END_MESSAGE_MAP()


// DlgMonsterTool 메시지 처리기


BOOL DlgMonsterTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_EventTypeComboBox.AddString(_T("Monster0"));
	m_EventTypeComboBox.AddString(_T("Monster1"));
	m_EventTypeComboBox.AddString(_T("Monster2"));
	m_EventTypeComboBox.AddString(_T("Monster3"));
	m_EventTypeComboBox.AddString(_T("Door1"));
	m_EventTypeComboBox.AddString(_T("Door2"));
	m_EventTypeComboBox.AddString(_T("Door3"));

	m_EventTypeComboBox.SetCurSel(-1);

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

void DlgMonsterTool::TriggerListBoxPick(int pickedNum)
{
	m_TriggerListBox.SetCurSel(pickedNum);
}


int DlgMonsterTool::GetCheckedButton()
{
	int TouchButtonManual = (int)(TriggerMethod::End);

	int Touch = m_TouchButtonManual1.GetCheck();
	int Button = m_TouchButtonManual2.GetCheck();
	int Manual = m_TouchButtonManual3.GetCheck();

	if (Touch)
		TouchButtonManual = (int)(TriggerMethod::Touch);
	else if (Button)
		TouchButtonManual = (int)(TriggerMethod::Button);
	else if (Manual)
		TouchButtonManual = (int)(TriggerMethod::Manual);

	return TouchButtonManual;
}


void DlgMonsterTool::SetCheckedButton(TriggerMethod Select)
{
	m_TouchButtonManual1.SetCheck(0);
	m_TouchButtonManual2.SetCheck(0);
	m_TouchButtonManual3.SetCheck(0);

	switch (Select)
	{
	case TriggerMethod::Touch:
		m_TouchButtonManual1.SetCheck(1);
		break;
	case TriggerMethod::Button:
		m_TouchButtonManual2.SetCheck(1);
		break;
	case TriggerMethod::Manual:
		m_TouchButtonManual3.SetCheck(1);
		break;
	}
}


void DlgMonsterTool::ClickAddTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int TouchButtonManual = GetCheckedButton();
	if (TouchButtonManual == (int)(TriggerMethod::End))	//Touch Button Manual 정하지 않았다면 취소
		return;

	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* Trigger = cam->Add_TriggerObject(m_TriggerCnt);
	Trigger->SetTriggerMethod((TriggerMethod)TouchButtonManual);

	wstring name = Trigger->GetGameObject()->name;
	m_TriggerListBox.AddString(name.c_str());

	int i = m_TriggerListBox.GetCount();
	m_TriggerListBox.SetCurSel(i - 1);

	//이벤트상자 비우기. 추후 확인
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);

	++m_TriggerCnt;
	SetCheckedButton(TriggerMethod::End);

	//scrollRot 디폴트로
	SetScaleScrollToDefault();
	SetRotationScrollToDefault();
}


void DlgMonsterTool::ClickRemoveTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Select = m_TriggerListBox.GetCurSel();
	if (Select == -1)
		return;

	Pickable::g_TriggerVec[Select]->Destroy();
	m_TriggerListBox.DeleteString(Select);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	m_TriggerListBox.SetCurSel(-1);
	giz->Detach();
	giz->enable = false;

	//이벤트상자 비우기. 추후 확인
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);
}


void DlgMonsterTool::OnLbnSelChangeTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Select = m_TriggerListBox.GetCurSel();
	if (Select == -1)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	Pickable* pick = Pickable::g_TriggerVec[Select];
	giz->Attach(pick->GetTransform());

	SetCheckedButton(pick->GetTriggerMethod());

	//몬스터상자 비우기. 추후 확인
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);

	//몬스터리스트상자 채우기
	std::vector<Pickable*> EventVec = pick->GetEventVec();
	int vecSize = EventVec.size();
	wstring name = L"";
	for (int i = 0; i < vecSize; ++i)
	{
		name = EventVec[i]->GetGameObject()->GetName();
		m_EventListBox.AddString(name.c_str());
	}

	//ScaleRot picked값으로 scroll 변경
	SetScaleScrollToPicked(pick);
	SetRotationScrollToPicked(pick);
}


void DlgMonsterTool::ClickAddEvent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerSelect = m_TriggerListBox.GetCurSel();
	
	if (TriggerSelect == -1)		//선택된 트리거가 없다면 취소
		return;

	int evtType = m_EventTypeComboBox.GetCurSel();

	if (evtType == -1)
		return;


	Pickable* trigger = Pickable::g_TriggerVec[TriggerSelect];

	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* EventObject = cam->Add_EventObject(trigger, m_EventCnt);
	EventType check = (EventType)m_EventTypeComboBox.GetCurSel();
	EventObject->SetEventType(check);

	++m_EventCnt;

	m_EventListBox.AddString(EventObject->GetGameObject()->GetName().c_str());
	m_EventListBox.SetCurSel(m_EventListBox.GetCount() - 1);
	m_EventTypeComboBox.SetCurSel(-1);

	//scrollRot 디폴트로
	SetScaleScrollToDefault();
	SetRotationScrollToDefault();
}


void DlgMonsterTool::ClickRemoveEvent()
{
	int TriggerSelect = m_TriggerListBox.GetCurSel();
	if (TriggerSelect == -1)
		return;

	int EventSelect = m_EventListBox.GetCurSel();
	if (EventSelect == -1)
		return;

	Pickable* Trigger = Pickable::g_TriggerVec[TriggerSelect];
	Trigger->RemoveEventObject(EventSelect);

	m_EventListBox.DeleteString(EventSelect);
	m_EventListBox.SetCurSel(-1);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->Detach();
	giz->enable = false;
}

void DlgMonsterTool::SetTwoListBox(int TriggerIndex, int EventIndex)
{
	int a = m_TriggerListBox.GetCount() -1;

	if (TriggerIndex > m_TriggerListBox.GetCount() || TriggerIndex <= -1)
		return;

	m_TriggerListBox.SetCurSel(TriggerIndex);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	//몬스터상자 비우기. 추후 확인
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);

	//몬스터리스트상자 채우기
	std::vector<Pickable*> EventVec = Pickable::g_TriggerVec[TriggerIndex]->GetEventVec();
	int vecSize = EventVec.size();
	wstring name = L"";
	for (int i = 0; i < vecSize; ++i)
	{
		name = EventVec[i]->GetGameObject()->GetName();
		m_EventListBox.AddString(name.c_str());
	}

	m_EventListBox.SetCurSel(EventIndex);
}

void DlgMonsterTool::PickedMethodToButton(int TriggerIndex)
{
	Pickable* Trigger = Pickable::g_TriggerVec[TriggerIndex];
	TriggerMethod method = Trigger->GetTriggerMethod();
	SetCheckedButton(method);
}

void DlgMonsterTool::ClearEverything()
{
	m_TriggerListBox.SetCurSel(-1);
	m_EventListBox.SetCurSel(-1);
	m_EventTypeComboBox.SetCurSel(-1);
	SetCheckedButton(TriggerMethod::End);

	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);			//몬스터리스트박스 비우기

	//scale,rot, 이름까지 초기화
	SetScaleScrollToDefault(nullptr);
	SetRotationScrollToDefault(nullptr);
	m_ChangingName = L"";

	UpdateData(false);
}

void DlgMonsterTool::SetScaleScrollToDefault(Pickable* picked)
{
	m_SliderScaleX.SetPos(20);
	m_SliderScaleY.SetPos(20);
	m_SliderScaleZ.SetPos(20);

	if (picked == nullptr || picked->GetType() == Type::Map)
		return;
	
	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->GetSelectedObject()->transform->SetScale(Vec3(1.f, 1.f, 1.f));
}

void DlgMonsterTool::SetRotationScrollToDefault(Pickable* picked)
{
	m_SliderRotationX.SetPos(180);
	m_SliderRotationY.SetPos(180);
	m_SliderRotationZ.SetPos(180);

	if (picked == nullptr || picked->GetType() == Type::Map)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->GetSelectedObject()->transform->SetEulerAngle(Vec3(0.f, 0.f, 0.f));
}

void DlgMonsterTool::SetScaleScrollToPicked(Pickable* picked)
{
	if (picked->GetType() == Type::Map)
		return;

	Transform* ParentTrnasform = picked->GetGameObject()->GetTransform();
	Vec3 Scale = ParentTrnasform->scale;
	float ScaleX = Scale.x * 20.f;
	float ScaleY = Scale.y * 20.f;
	float ScaleZ = Scale.z * 20.f;

	//m_SliderScaleX.SetPos((int)ScaleX);
	//m_SliderScaleY.SetPos((int)ScaleY);
	//m_SliderScaleZ.SetPos((int)ScaleZ);

	m_SliderScaleX.SetPos(10);
	m_SliderScaleY.SetPos(10);
	m_SliderScaleZ.SetPos(10);
}

void DlgMonsterTool::SetRotationScrollToPicked(Pickable* picked)
{
	if (picked->GetType() == Type::Map)
		return;

	Transform* ParentTrnasform = picked->GetGameObject()->GetTransform();
	Vec3 Rotation = ParentTrnasform->rotation;

	float RotationX = Rotation.x + 180.f;
	float RotationY = Rotation.y + 180.f;
	float RotationZ = Rotation.z + 180.f;

	m_SliderScaleX.SetPos((int)RotationX);
	m_SliderScaleY.SetPos((int)RotationY);
	m_SliderScaleZ.SetPos((int)RotationZ);
}


void DlgMonsterTool::OnLbnSelChangeEvent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerSelect = m_TriggerListBox.GetCurSel();
	if (TriggerSelect == -1)
		return;
	
	int EventSelect = m_EventListBox.GetCurSel();
	if (EventSelect == -1)
		return;

	Pickable* trigger = Pickable::g_TriggerVec[TriggerSelect];

	std::vector<Pickable*> EventVec = trigger->GetEventVec();

	Pickable* Event = EventVec[EventSelect];
	//
	wstring name = Event->GetGameObject()->name;
	EventType check1= Event->GetEventType();
	int check2 = (int)check1;
	//
	m_EventTypeComboBox.SetCurSel(check2);

	TriggerMethod method = trigger->GetTriggerMethod();
	SetCheckedButton(method);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	giz->Attach(Event->transform);

	//ScaleRot picked값으로 scroll 변경
	SetScaleScrollToPicked(Event);
	SetRotationScrollToPicked(Event);
}


void DlgMonsterTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (!trans)
		return;

	Pickable* picked = trans->GetGameObject()->GetComponent<Pickable>();

	if (!picked)
		return;

	if (picked->GetType() == Type::Map)
		return;

	float ScaleX = float(m_SliderScaleX.GetPos() / 20.f);
	float ScaleY = float(m_SliderScaleY.GetPos() / 20.f);
	float ScaleZ = float(m_SliderScaleZ.GetPos() / 20.f);
	giz->GetSelectedObject()->transform->SetScale(Vec3(ScaleX, ScaleY, ScaleZ));

	float RotateX = float(m_SliderRotationX.GetPos() - 180);
	float RotateY = float(m_SliderRotationY.GetPos() - 180);
	float RotateZ = float(m_SliderRotationZ.GetPos() - 180);
	giz->GetSelectedObject()->transform->SetEulerAngle(Vec3(RotateX, RotateY, RotateZ));

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgMonsterTool::OnClickedTriggerMethodApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerIndex = m_TriggerListBox.GetCurSel();
	if (TriggerIndex == -1)
		return;
	
	Pickable* Trigger = Pickable::g_TriggerVec[TriggerIndex];
	Trigger->SetTriggerMethod((TriggerMethod)GetCheckedButton());
	
}


void DlgMonsterTool::OnClickedEventTypeApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerIndex = m_TriggerListBox.GetCurSel();
	if (TriggerIndex == -1)
		return;

	int EventIndex = m_EventListBox.GetCurSel();
	if (EventIndex == -1)
		return;

	std::vector<Pickable*> EventVec = Pickable::g_TriggerVec[TriggerIndex]->GetEventVec();
	Pickable* EventObj = EventVec[EventIndex];

	EventObj->SetEventType(EventType(m_EventTypeComboBox.GetCurSel()));
}


void DlgMonsterTool::OnBnClickedChangeTriggerName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerSelect = m_TriggerListBox.GetCurSel();
	if (TriggerSelect == -1)
		return;

	UpdateData(true);

	std::vector<Pickable*> TriggerVec = Pickable::g_TriggerVec;

	GameObject* ParentObj = TriggerVec[TriggerSelect]->GetGameObject();
	ParentObj->name = m_ChangingName.GetString();

	m_TriggerListBox.ResetContent();
	for (unsigned int i = 0; i < TriggerVec.size(); ++i)
	{
		CString name = TriggerVec[i]->GetGameObject()->name.c_str();
		m_TriggerListBox.AddString(name);
	}
	m_TriggerListBox.SetCurSel(TriggerSelect);
}


void DlgMonsterTool::OnBnClickedChangeEventName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerSelect = m_TriggerListBox.GetCurSel();
	int EventSelect = m_EventListBox.GetCurSel();
	if (TriggerSelect == -1 || EventSelect == -1)
		return;

	UpdateData(true);

	std::vector<Pickable*> TriggerVec = Pickable::g_TriggerVec;
	Pickable* TriggerObj = TriggerVec[TriggerSelect];
	std::vector<Pickable*> EventVec = TriggerObj->GetEventVec();
	Pickable* EventObj = EventVec[EventSelect];

	GameObject* ParentObj = EventObj->GetGameObject();

	ParentObj->name = m_ChangingName.GetString();

	m_EventListBox.ResetContent();
	for (unsigned int i = 0; i < EventVec.size(); ++i)
	{
		CString name = EventVec[i]->GetGameObject()->name.c_str();
		m_EventListBox.AddString(name);
	}
	m_EventListBox.SetCurSel(EventSelect);
}


void DlgMonsterTool::OnBnClickedResetScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	
	if (trans == nullptr)
	{
		SetScaleScrollToDefault(nullptr);
		return;
	}

	Pickable* picked = trans->GetGameObject()->GetComponent<Pickable>();

	SetScaleScrollToDefault(picked);
}


void DlgMonsterTool::OnBnClickedResetRotation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();

	if (trans == nullptr)
	{
		SetRotationScrollToDefault(nullptr);
		return;
	}

	Pickable* picked = trans->GetGameObject()->GetComponent<Pickable>();

	SetRotationScrollToDefault(picked);
}
