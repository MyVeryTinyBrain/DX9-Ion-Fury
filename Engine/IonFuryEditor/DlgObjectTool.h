#pragma once

// DlgObjectTool 대화 상자

class HandlingObject;

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
	CSliderCtrl m_SliderScaleX;
	CSliderCtrl m_SliderScaleY;
	CSliderCtrl m_SliderScaleZ;
	CSliderCtrl m_SliderRotationX;
	CSliderCtrl m_SliderRotationY;
	CSliderCtrl m_SliderRotationZ;
	CSliderCtrl m_PivotSliderScale;
	CComboBox m_TypeComboBox;
	CString m_Name;
	int m_Cnt = 0;
public:
	void SetScaleScrollToDefault(HandlingObject* picked = nullptr);		
	void SetRotationScrollToDefault(HandlingObject* picked = nullptr);	//매개변수 있으면 reset, 아니면 스크롤값 초기화
	void SetScaleScrollToPicked(HandlingObject* picked);
	void SetRotationScrollToPicked(HandlingObject* picked);
public:
	void SetComboBoxAsSelected(HandlingObject* picked);
	void UndoToolStatus();
public:
	void SaveToJsonFormat(const Json::Value& json, string path);
	Json::Value LoadFromJsonFormat(string path);
	wstring ToWString(const string& str);
	string ToString(const wstring& wstr);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedResetType();
	afx_msg void OnBnClickedRenameButton();
	afx_msg void OnLbnSelchangeListBox();

	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedResetScale();
	afx_msg void OnBnClickedResetRotation();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
