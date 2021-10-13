﻿// DlgMonsterTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgMonsterTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "Pickable.h"
#include "Gizmo.h"

// DlgMonsterTool 대화 상자

IMPLEMENT_DYNAMIC(DlgMonsterTool, CDialog)

DlgMonsterTool::DlgMonsterTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgMonsterTool, pParent)
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
}


BEGIN_MESSAGE_MAP(DlgMonsterTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgMonsterTool::ClickAddTrigger)
	ON_BN_CLICKED(IDC_BUTTON8, &DlgMonsterTool::ClickRemoveTrigger)
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgMonsterTool::OnLbnSelChangeTrigger)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgMonsterTool::ClickAddEvent)
END_MESSAGE_MAP()


// DlgMonsterTool 메시지 처리기


BOOL DlgMonsterTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgMonsterTool::TriggerListBoxPick(int pickedNum)
{
	m_TriggerListBox.SetCurSel(pickedNum);
}


void DlgMonsterTool::ClickAddTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* Trigger = cam->Add_TriggerObject(m_TriggerCnt);
	++m_TriggerCnt;

	wstring name = Trigger->GetGameObject()->name;
	m_TriggerListBox.AddString(name.c_str());

	int i = m_TriggerListBox.GetCount();
	m_TriggerListBox.SetCurSel(i - 1);

	//이벤트상자 비우기. 추후 확인
	for (int i = m_EventListBox.GetCount(); i > 0; --i)
		m_EventListBox.DeleteString(i - 1);
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
}


void DlgMonsterTool::ClickAddEvent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int TriggerSelect = m_TriggerListBox.GetCurSel();
	int TouchButtonManual = 0;
	
	int Touch = m_TouchButtonManual1.GetCheck();
	int Button = m_TouchButtonManual2.GetCheck();
	int Manual = m_TouchButtonManual3.GetCheck();
	//if(Touch)

	//if (TriggerSelect == -1 ||)
	//	return;

	Pickable* trigger = Pickable::g_TriggerVec[TriggerSelect];

	FreePerspectiveCamera* cam = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* EventObject = cam->Add_EventObject(trigger, m_EventCnt);
	++m_EventCnt;

	m_EventListBox.AddString(EventObject->GetGameObject()->GetName().c_str());

	
}
