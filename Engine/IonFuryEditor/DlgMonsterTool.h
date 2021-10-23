#pragma once


// DlgMonsterTool 대화 상자

#include "EditorEnum.h"
#include <fstream>
#include <atlconv.h>
#include "../json/json.h"

class Pickable;

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
	int	GetCheckedButton();
	void SetCheckedButton(TriggerMethod Select);
	void SetTwoListBox(int TriggerIndex, int EventIndex);

	void PickedMethodToButton(int TriggerIndex);
	void ClearEverything();

	void SetScaleScrollToDefault(Pickable* picked = nullptr);
	void SetRotationScrollToDefault(Pickable* picked = nullptr);
	void SetScaleScrollToPicked(Pickable* picked);
	void SetRotationScrollToPicked(Pickable* picked);
public:
	void SaveToJsonFormat(const Json::Value& json, string path);
	Json::Value LoadFromJsonFormat(string path);
	wstring ToWString(const string& str);
	string ToString(const wstring& wstr);

	void EmptyBeforeLoad();
	void EmptyAfterLoad();
	Pickable* AddTriggerLoadingStyle(wstring name, Vec3 Pos, Vec3 Scale, Vec3 Euler, TriggerMethod method, bool TriggerOnce);
	void AddEventLoadingStyle(Pickable* Trigger, wstring name, Vec3 Pos, Vec3 Scale, Vec3 Euler, EventType type);
public:
	int m_TriggerCnt = 0;
	int m_EventCnt = 0;
public:
	CListBox m_TriggerListBox;
	CListBox m_EventListBox;

	CButton m_TouchButtonManual1;
	CButton m_TouchButtonManual2;
	CButton m_TouchButtonManual3;
	
	CComboBox m_EventTypeComboBox;
	
	CSliderCtrl m_SliderRotationX;
	CSliderCtrl m_SliderRotationY;
	CSliderCtrl m_SliderRotationZ;
	// ScaleX
	CSliderCtrl m_SliderScaleX;
	CSliderCtrl m_SliderScaleY;
	CSliderCtrl m_SliderScaleZ;

	CString m_ChangingName;
	CButton m_TriggerOnce;
public:
	afx_msg void ClickRemoveTrigger();
	afx_msg void ClickAddTrigger();
	afx_msg void ClickAddEvent();
	afx_msg void OnLbnSelChangeTrigger();
	afx_msg void OnLbnSelChangeEvent();
	afx_msg void ClickRemoveEvent();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickedTriggerMethodApply();
	afx_msg void OnClickedEventTypeApply();
	afx_msg void OnBnClickedChangeTriggerName();
	afx_msg void OnBnClickedChangeEventName();
	afx_msg void OnBnClickedResetScale();
	afx_msg void OnBnClickedResetRotation();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedLoadButton();
};
