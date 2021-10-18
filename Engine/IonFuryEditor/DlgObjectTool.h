#pragma once


// DlgObjectTool 대화 상자

class DlgObjectTool : public CDialog
{
	DECLARE_DYNAMIC(DlgObjectTool)

public:
	DlgObjectTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgObjTool };
#endif
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton16();
};
