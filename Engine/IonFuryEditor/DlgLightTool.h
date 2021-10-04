#pragma once


// DlgLightTool 대화 상자

class DlgLightTool : public CDialog
{
	DECLARE_DYNAMIC(DlgLightTool)

public:
	DlgLightTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgLightTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgLightTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL ABCMEMBER;
	afx_msg void lighttooltouchtouchyeasbays();
};
