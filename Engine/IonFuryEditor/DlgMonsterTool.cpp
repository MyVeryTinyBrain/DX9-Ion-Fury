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

//#include <iostream>
#include <fstream>
#include <atlconv.h>
//#include "../json/json.h"

// DlgMonsterTool 대화 상자

IMPLEMENT_DYNAMIC(DlgMonsterTool, CDialog)

DlgMonsterTool::DlgMonsterTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgMonsterTool, pParent)
	, m_ChangingName(_T(""))
	, m_PosX(0)
	, m_PosY(0)
	, m_PosZ(0)
	, m_ScaleX(0)
	, m_ScaleY(0)
	, m_RotX(0)
	, m_RotY(0)
	, m_RotZ(0)
	, m_ScaleZ(0)
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
	DDX_Control(pDX, IDC_RADIO1, m_TouchButtonManual4);
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
	DDX_Control(pDX, IDC_CHECK1, m_TriggerOnce);
	DDX_Text(pDX, IDC_EDIT2, m_PosX);
	DDX_Text(pDX, IDC_EDIT3, m_PosY);
	DDX_Text(pDX, IDC_EDIT4, m_PosZ);
	DDX_Text(pDX, IDC_EDIT5, m_ScaleX);
	DDX_Text(pDX, IDC_EDIT6, m_ScaleY);
	DDX_Text(pDX, IDC_EDIT7, m_ScaleZ);
	DDX_Text(pDX, IDC_EDIT8, m_RotX);
	DDX_Text(pDX, IDC_EDIT9, m_RotY);
	DDX_Text(pDX, IDC_EDIT10, m_RotZ);
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
	ON_BN_CLICKED(IDC_BUTTON11, &DlgMonsterTool::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_BUTTON12, &DlgMonsterTool::OnBnClickedLoadButton)
	ON_BN_CLICKED(IDC_BUTTON6, &DlgMonsterTool::OnBnClickedPositionApplyButton)
	ON_BN_CLICKED(IDC_BUTTON7, &DlgMonsterTool::OnBnClickedScaleApplyButton)
	ON_BN_CLICKED(IDC_BUTTON20, &DlgMonsterTool::OnBnClickedRotationApplyButton)
END_MESSAGE_MAP()


// DlgMonsterTool 메시지 처리기


BOOL DlgMonsterTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_EventTypeComboBox.AddString(_T("Basic Mutant"));
	m_EventTypeComboBox.AddString(_T("Mutant"));
	m_EventTypeComboBox.AddString(_T("Cultist Archer"));
	m_EventTypeComboBox.AddString(_T("Greater Gunner"));
	m_EventTypeComboBox.AddString(_T("Deacon"));
	m_EventTypeComboBox.AddString(_T("Drone"));
	m_EventTypeComboBox.AddString(_T("Liberator"));
	m_EventTypeComboBox.AddString(_T("Spider"));
	m_EventTypeComboBox.AddString(_T("Skull"));
	m_EventTypeComboBox.AddString(_T("Warmech"));
	m_EventTypeComboBox.AddString(_T("Wendigo"));

	m_EventTypeComboBox.AddString(_T("ObjectAutoDoor"));
	m_EventTypeComboBox.AddString(_T("ObjectManualDoor"));
	m_EventTypeComboBox.AddString(_T("ObjectCardScreen"));
	m_EventTypeComboBox.AddString(_T("ObjectButton"));

	m_EventTypeComboBox.AddString(_T("ObjectMiniGame"));
	
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
	int CardCheck = m_TouchButtonManual4.GetCheck();

	if (Touch)
		TouchButtonManual = (int)(TriggerMethod::Touch);
	else if (Button)
		TouchButtonManual = (int)(TriggerMethod::Button);
	else if (Manual)
		TouchButtonManual = (int)(TriggerMethod::Manual);
	else if (CardCheck)
		TouchButtonManual = (int)(TriggerMethod::CardCheck);

	return TouchButtonManual;
}


void DlgMonsterTool::SetCheckedButton(TriggerMethod Select)
{
	m_TouchButtonManual1.SetCheck(0);
	m_TouchButtonManual2.SetCheck(0);
	m_TouchButtonManual3.SetCheck(0);
	m_TouchButtonManual4.SetCheck(0);

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
	case TriggerMethod::CardCheck:
		m_TouchButtonManual4.SetCheck(1);
		break;
	}
}


void DlgMonsterTool::ClickAddTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int TouchButtonManual = GetCheckedButton();
	if (TouchButtonManual == (int)(TriggerMethod::End))	//Touch Button Manual 정하지 않았다면 취소
		return;

	bool TriggerOnce = m_TriggerOnce.GetCheck();

	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* Trigger = cam->Add_TriggerObject(m_TriggerCnt);
	Trigger->SetNoLightTransparentMaterial();
	Trigger->SetTriggerMethod((TriggerMethod)TouchButtonManual);
	Trigger->SetTriggerOnce(TriggerOnce);
	
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
	m_TriggerOnce.SetCheck(pick->GetTriggerOnce());

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

	Transform* trans = giz->GetSelectedObject();
	SetEditStatusFromGiz(trans->position, trans->scale, trans->eulerAngle);
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
	EventObject->SetComponentToPickable(check);
	EventObject->SetOverSeeBlackMaterial();


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

void DlgMonsterTool::EmptyBeforeLoad()
{
	Pickable::ClearTriggerVector();

	for (int i = m_TriggerListBox.GetCount(); i > 0; --i)
		m_TriggerListBox.DeleteString(i - 1);		//트리거리스트박스 비우기
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);			//몬스터리스트박스 비우기

	SetCheckedButton(TriggerMethod::End);
	m_EventTypeComboBox.SetCurSel(-1);
	SetScaleScrollToDefault(nullptr);
	SetRotationScrollToDefault(nullptr);
	m_ChangingName = L"";

	UpdateData(false);
}

void DlgMonsterTool::EmptyAfterLoad()
{
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);			//몬스터리스트박스 비우기
	
	SetScaleScrollToDefault(nullptr);
	SetRotationScrollToDefault(nullptr);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->Detach();
	giz->enable = false;
}

Pickable* DlgMonsterTool::AddTriggerLoadingStyle(wstring name, Vec3 Pos, Vec3 Scale, Vec3 Euler, TriggerMethod method, bool TriggerOnce)
{
	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	
	Pickable* Trigger = cam->Add_TriggerObject(m_TriggerCnt);
	Transform* trans = Trigger->GetGameObject()->GetTransform();

	Trigger->SetNoLightTransparentMaterial();
	trans->GetGameObject()->name = name;
	trans->SetPosition(Pos);
	trans->SetScale(Scale);
	trans->SetEulerAngle(Euler);
	Trigger->SetTriggerMethod(method);
	Trigger->SetTriggerOnce(TriggerOnce);

	m_TriggerListBox.AddString(name.c_str());

	//int i = m_TriggerListBox.GetCount();
	//m_TriggerListBox.SetCurSel(i - 1);

	//이벤트상자 비우기. 추후 확인
	//for (int i = m_EventListBox.GetCount(); i > 0; --i)
	//	m_EventListBox.DeleteString(i - 1);

	return Trigger;
}

void DlgMonsterTool::AddEventLoadingStyle(Pickable* Trigger, wstring name, Vec3 Pos, Vec3 Scale, Vec3 Euler, EventType type)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* EventObject = cam->Add_EventObject(Trigger, m_EventCnt);
	EventObject->SetEventType(type);

	Transform* trans = EventObject->GetGameObject()->GetTransform();
	trans->GetGameObject()->name = name;
	trans->SetPosition(Pos);
	//trans->SetScale(Scale);
	//trans->SetEulerAngle(Euler);
	EventObject->SetEventType(type);
	EventObject->SetComponentToPickable(type);
	trans->SetScale(Scale);
	trans->SetEulerAngle(Euler);
	EventObject->GetChildObject()->transform->scale = Vec3(0.5, 0.5f, 0.5f);
	EventObject->SetOverSeeBlackMaterial();

	m_EventListBox.AddString(name.c_str());

	++m_EventCnt;
}

void DlgMonsterTool::StatusWhileMouseMove(Pickable* picked)
{
	UpdateData(TRUE);
	Transform* trans = picked->GetGameObject()->GetTransform();
	m_PosX = trans->position.x;
	m_PosY = trans->position.y;
	m_PosZ = trans->position.z;
	UpdateData(FALSE);
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
	giz->GetSelectedObject()->GetGameObject()->GetComponent<Pickable>()->GetChildObject()->transform->scale = Vec3(0.5f, 0.5f, 0.5f);
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

	Transform* ParentTransform = picked->GetGameObject()->GetTransform();
	Vec3 Scale = ParentTransform->scale;

	float ScaleX = Scale.x * 20.f;
	float ScaleY = Scale.y * 20.f;
	float ScaleZ = Scale.z * 20.f;

	m_SliderScaleX.SetPos((int)ScaleX);
	m_SliderScaleY.SetPos((int)ScaleY);
	m_SliderScaleZ.SetPos((int)ScaleZ);
}

void DlgMonsterTool::SetRotationScrollToPicked(Pickable* picked)
{
	if (picked->GetType() == Type::Map)
		return;

	Transform* ParentTransform = picked->GetGameObject()->GetTransform();

	Vec3 EulerAngle = ParentTransform->GetEulerAngle();

	float RotationX = EulerAngle.x + 180;
	float RotationY = EulerAngle.y + 180;
	float RotationZ = EulerAngle.z + 180;

	m_SliderRotationX.SetPos((int)RotationX);
	m_SliderRotationY.SetPos((int)RotationY);
	m_SliderRotationZ.SetPos((int)RotationZ);
}

void DlgMonsterTool::SetEditStatusFromGiz(Vec3 Pos, Vec3 Scale, Vec3 EulerAngle)
{
	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	auto trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;

	Pickable* Picked = trans->GetGameObject()->GetComponent<Pickable>();
	if (Picked == nullptr)
		return;

	if (Picked->GetType() == Type::Map)
		return;
	//오류방지턱

	m_PosX = Pos.x;
	m_PosY = Pos.y;
	m_PosZ = Pos.z;
	m_ScaleX = Scale.x;
	m_ScaleY = Scale.y;
	m_ScaleZ = Scale.z;
	m_RotX = EulerAngle.x;
	m_RotY = EulerAngle.y;
	m_RotZ = EulerAngle.z;

	UpdateData(FALSE);
}

void DlgMonsterTool::SaveToJsonFormat(const Json::Value& json, string path)
{
	Json::StreamWriterBuilder builder;
	string jsonFormatText = Json::writeString(builder, json);

	std::ofstream out;
	out.open(path);

	out << jsonFormatText;

	out.close();
}

Json::Value DlgMonsterTool::LoadFromJsonFormat(string path)
{
	std::ifstream in;
	in.open(path);

	if (!in.is_open())
	{
		cout << "json read error: not exist file" << endl;
		return Json::Value();
	}

	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	std::string jsonFormatText(size, ' ');
	in.seekg(0);
	in.read(&jsonFormatText[0], size);

	in.close();

	Json::Value root;
	JSONCPP_STRING err;

	Json::CharReaderBuilder charReaderBuilder;
	const std::unique_ptr<Json::CharReader> reader(charReaderBuilder.newCharReader());
	if (!reader->parse(jsonFormatText.c_str(), jsonFormatText.c_str() + jsonFormatText.length(), &root, &err))
	{
		cout << "json read error: invalid format" << endl;
		return EXIT_FAILURE;
	}

	return root;
}

wstring DlgMonsterTool::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string DlgMonsterTool::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
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

	if (TriggerSelect >= Pickable::g_TriggerVec.size())/////////////////////////1022추가
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
	bool TriggerOnce = trigger->GetTriggerOnce();
	SetCheckedButton(method);
	m_TriggerOnce.SetCheck(TriggerOnce);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	giz->Attach(Event->transform);

	//ScaleRot picked값으로 scroll 변경
	SetScaleScrollToPicked(Event);
	SetRotationScrollToPicked(Event);

	Transform* trans = giz->GetSelectedObject();
	SetEditStatusFromGiz(trans->position, trans->scale, trans->eulerAngle);
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
	
	if (picked->GetType() == Type::EventObject)
	{
		picked->GetChildObject()->transform->scale = Vec3(0.5f, 0.5f, 0.5f);
	}
	

	float RotateX = float(m_SliderRotationX.GetPos() - 180);
	float RotateY = float(m_SliderRotationY.GetPos() - 180);
	float RotateZ = float(m_SliderRotationZ.GetPos() - 180);
	picked->GetGameObject()->transform->SetEulerAngle(Vec3(RotateX, RotateY, RotateZ));


	SetEditStatusFromGiz(trans->position, trans->scale, trans->eulerAngle);
	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgMonsterTool::OnClickedTriggerMethodApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerIndex = m_TriggerListBox.GetCurSel();
	if (TriggerIndex == -1)
		return;
	bool TriggerOnce = m_TriggerOnce.GetCheck();


	Pickable* Trigger = Pickable::g_TriggerVec[TriggerIndex];
	Trigger->SetTriggerMethod((TriggerMethod)GetCheckedButton());

	Trigger->SetTriggerOnce(TriggerOnce);
	
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


void DlgMonsterTool::OnBnClickedSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"txt", L"TriggerEventData.txt", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data\\TriggerEvent");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		Json::Value Root;

		std::vector<Pickable*> TriggerVec = Pickable::g_TriggerVec;
		for (unsigned int i = 0; i < TriggerVec.size(); ++i)
		{
			Pickable* TriggerObject = TriggerVec[i];

			Json::Value Trigger;

			{
				Json::Value TriggerValue;
				TriggerValue["Name"] = ToString(TriggerObject->GetGameObject()->GetName());
				TriggerValue["PositionX"] = TriggerObject->GetGameObject()->GetTransform()->position.x;
				TriggerValue["PositionY"] = TriggerObject->GetGameObject()->GetTransform()->position.y;
				TriggerValue["PositionZ"] = TriggerObject->GetGameObject()->GetTransform()->position.z;
				TriggerValue["ScaleX"] = TriggerObject->GetGameObject()->GetTransform()->scale.x;
				TriggerValue["ScaleY"] = TriggerObject->GetGameObject()->GetTransform()->scale.y;
				TriggerValue["ScaleZ"] = TriggerObject->GetGameObject()->GetTransform()->scale.z;
				TriggerValue["RotationX"] = TriggerObject->GetGameObject()->transform->eulerAngle.x;
				TriggerValue["RotationY"] = TriggerObject->GetGameObject()->transform->eulerAngle.y;
				TriggerValue["RotationZ"] = TriggerObject->GetGameObject()->transform->eulerAngle.z;
				TriggerValue["TriggerMethod"] = (int)TriggerObject->GetTriggerMethod();
				TriggerValue["TriggerOnce"] = TriggerObject->GetTriggerOnce();
				TriggerValue["TriggerToolAutoNum"] = m_TriggerCnt;

				Trigger[0] = TriggerValue;
			}

			//Trigger[1~] = Event
			std::vector<Pickable*> EventVec = TriggerObject->GetEventVec();
			for (unsigned int j = 0; j < EventVec.size(); ++j)
			{
				Json::Value Event;
				Pickable* EventObject = EventVec[j];
				Event["Name"] = ToString(EventObject->GetGameObject()->GetName());
				Event["PositionX"] = EventObject->GetGameObject()->GetTransform()->position.x;
				Event["PositionY"] = EventObject->GetGameObject()->GetTransform()->position.y;
				Event["PositionZ"] = EventObject->GetGameObject()->GetTransform()->position.z;
				Event["ScaleX"] = EventObject->GetGameObject()->GetTransform()->scale.x;
				Event["ScaleY"] = EventObject->GetGameObject()->GetTransform()->scale.y;
				Event["ScaleZ"] = EventObject->GetGameObject()->GetTransform()->scale.z;
				Event["RotationX"] = EventObject->GetGameObject()->transform->eulerAngle.x;
				Event["RotationY"] = EventObject->GetGameObject()->transform->eulerAngle.y;
				Event["RotationZ"] = EventObject->GetGameObject()->transform->eulerAngle.z;
				Event["EventType"] = (int)(EventObject->GetEventType());

				Trigger[j + 1] = Event;
			}

			//Root[i] = Trigger
			Root[i] = Trigger;
		}

		SaveToJsonFormat(Root, ToString(wstrFilePath.GetString()));
	}
}


void DlgMonsterTool::OnBnClickedLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L"txt", L"*.txt", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH]{};

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data\\TriggerEvent");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		EmptyBeforeLoad();

		CString wstrFilePath = Dlg.GetPathName();
		
		Json::Value root = LoadFromJsonFormat(ToString(wstrFilePath.GetString()));
		int RootSize = (int)root.size();

		for (int i = 0; i < RootSize; ++i)
		{
			//Trigger
			Json::Value Trigger = root[i];
			Json::Value TriggerValue = Trigger[0];
			wstring Name = ToWString(TriggerValue["Name"].asString());
			Vec3 Pos = Vec3(TriggerValue["PositionX"].asFloat(), TriggerValue["PositionY"].asFloat(), TriggerValue["PositionZ"].asFloat());
			Vec3 Scale = Vec3(TriggerValue["ScaleX"].asFloat(), TriggerValue["ScaleY"].asFloat(), TriggerValue["ScaleZ"].asFloat());
			Vec3 EulerAngle = Vec3(TriggerValue["RotationX"].asFloat(), TriggerValue["RotationY"].asFloat(), TriggerValue["RotationZ"].asFloat());
			int temp = TriggerValue["TriggerMethod"].asInt();
			TriggerMethod method = (TriggerMethod)temp;
			bool TriggerOnce = TriggerValue["TriggerOnce"].asBool();

			Pickable* TriggerObject = AddTriggerLoadingStyle(Name, Pos, Scale, EulerAngle, method, TriggerOnce);	//트리거 로딩
			m_TriggerCnt = TriggerValue["TriggerToolAutoNum"].asInt();												//트리거 이름 자동완성 번호 셋팅


			int TriggerSize = Trigger.size();
			for (int i = 1; i < TriggerSize; ++i)
			{
				Json::Value Event = Trigger[i];

				wstring Name = ToWString(Event["Name"].asString());
				Vec3 Pos = Vec3(Event["PositionX"].asFloat(), Event["PositionY"].asFloat(), Event["PositionZ"].asFloat());
				Vec3 Scale = Vec3(Event["ScaleX"].asFloat(), Event["ScaleY"].asFloat(), Event["ScaleZ"].asFloat());
				Vec3 EulerAngle = Vec3(Event["RotationX"].asFloat(), Event["RotationY"].asFloat(), Event["RotationZ"].asFloat());
				int temp = Event["EventType"].asInt();
				EventType evtType = (EventType)(temp);

				AddEventLoadingStyle(TriggerObject, Name, Pos, Scale, EulerAngle, evtType);			//해당 트리거의 이벤트 로딩
			}
		}

		EmptyAfterLoad();
	}
}


void DlgMonsterTool::OnBnClickedPositionApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	auto trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;

	Pickable* Picked = trans->GetGameObject()->GetComponent<Pickable>();
	if (Picked == nullptr)
		return;

	if (Picked->GetType() == Type::Map)
		return;
	//오류방지턱

	trans->position = Vec3(m_PosX, m_PosY, m_PosZ);

	UpdateData(FALSE);
}


void DlgMonsterTool::OnBnClickedScaleApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	auto trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;

	Pickable* Picked = trans->GetGameObject()->GetComponent<Pickable>();
	if (Picked == nullptr)
		return;

	if (Picked->GetType() == Type::Map)
		return;
	//오류방지턱

	trans->scale = Vec3(m_ScaleX, m_ScaleY, m_ScaleZ);
	if (Picked->GetType() == Type::EventObject)
		Picked->GetChildObject()->transform->scale = Vec3(0.5f, 0.5f, 0.5f);

	m_SliderScaleX.SetPos((int)(m_ScaleX * 20));
	m_SliderScaleY.SetPos((int)(m_ScaleY * 20));
	m_SliderScaleZ.SetPos((int)(m_ScaleZ * 20));

	UpdateData(FALSE);
}


void DlgMonsterTool::OnBnClickedRotationApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	auto trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;

	Pickable* Picked = trans->GetGameObject()->GetComponent<Pickable>();
	if (Picked == nullptr)
		return;

	if (Picked->GetType() == Type::Map)
		return;
	//오류방지턱

	trans->eulerAngle = Vec3(m_RotX, m_RotY, m_RotZ);

	m_SliderRotationX.SetPos((int)(m_RotX + 180));
	m_SliderRotationY.SetPos((int)(m_RotY + 180));
	m_SliderRotationZ.SetPos((int)(m_RotZ + 180));
}
