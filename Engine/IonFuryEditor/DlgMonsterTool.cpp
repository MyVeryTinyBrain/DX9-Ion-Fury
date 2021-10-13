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
}


BEGIN_MESSAGE_MAP(DlgMonsterTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgMonsterTool::ClickAddTrigger)
	ON_BN_CLICKED(IDC_BUTTON8, &DlgMonsterTool::ClickRemoveTrigger)
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgMonsterTool::OnLbnSelChangeTrigger)
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
	Pickable* Trigger = cam->Add_MonsterToolObject(Type::Trigger, m_TriggerCnt);
	++m_TriggerCnt;

	wstring name = Trigger->GetGameObject()->name;
	m_TriggerListBox.AddString(name.c_str());

	int i = m_TriggerListBox.GetCount();
	m_TriggerListBox.SetCurSel(i - 1);

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

}


void DlgMonsterTool::OnLbnSelChangeTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Select = m_TriggerListBox.GetCurSel();
	if (Select == -1)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	giz->Attach(Pickable::g_TriggerVec[Select]->GetTransform());
}
