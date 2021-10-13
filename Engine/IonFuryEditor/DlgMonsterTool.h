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
	int m_EventCnt = 0;
public:
	CListBox m_TriggerListBox;
	CListBox m_EventListBox;

	CButton m_TouchButtonManual1;
	CButton m_TouchButtonManual2;
	CButton m_TouchButtonManual3;
public:
	afx_msg void ClickRemoveTrigger();
	afx_msg void ClickAddTrigger();
	afx_msg void ClickAddEvent();
	afx_msg void OnLbnSelChangeTrigger();
};
