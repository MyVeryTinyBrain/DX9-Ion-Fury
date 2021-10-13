#pragma once


// DlgMonsterTool 대화 상자

class DlgMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(DlgMonsterTool)

public:
	DlgMonsterTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgMonsterTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgMonsterTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	void TriggerListBoxPick(int pickedNum);
public:
	int m_TriggerCnt = 0;
	int m_MonsterCnt = 0;
public:
	CListBox m_TriggerListBox;
	afx_msg void ClickRemoveTrigger();
	afx_msg void ClickAddTrigger();
	afx_msg void OnLbnSelChangeTrigger();
};
