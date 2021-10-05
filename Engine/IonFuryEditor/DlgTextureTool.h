#pragma once


// DlgTextureTool 대화 상자

class DlgTextureTool : public CDialog
{
	DECLARE_DYNAMIC(DlgTextureTool)

public:
	DlgTextureTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgTextureTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgTextureTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
