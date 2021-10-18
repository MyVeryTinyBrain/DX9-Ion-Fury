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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CListBox m_ObjectListBox;
	CSliderCtrl m_ScaleXSlider;
	CSliderCtrl m_ScaleYSlider;
	CSliderCtrl m_ScaleZSlider;
	CSliderCtrl m_RotationXSlider;
	CSliderCtrl m_RotationYSlider;
	CSliderCtrl m_RotationZSlider;
	CSliderCtrl m_PivotScaleSlider;
	CComboBox m_TypeComboBox;
	CString m_Name;
	int m_Cnt = 0;
public:
	afx_msg void OnBnClickedAddButton();
public:
	virtual BOOL OnInitDialog();
};
