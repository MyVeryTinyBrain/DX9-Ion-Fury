#pragma once

// DlgObjectTool 대화 상자

#include "EditorEnum.h"

class Pickable;

class DlgObjectTool : public CDialog
{
	DECLARE_DYNAMIC(DlgObjectTool)

public:
	void SetPickableObject(GameObject* gameobject);
	void SelectObject();

public:
	DlgObjectTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgObjectTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void ResetScroll();
	void ReturnComboBoxSelect(Pickable* pick);
	void UpdateUVScale(Pickable* pick);

public:
	float EditToNum(const CEdit& edit);
	void NumToEdit(CEdit& edit, float num);

public:
	Vec2 GetToolUVScale();
public:
	CComboBox m_comboBox;

	CString m_objectName;
	
	CString m_meshPath;

	COMBOBOX m_MeshType;

	virtual BOOL OnInitDialog();
	afx_msg void OnObjectName();
	afx_msg void OnSelectMesh();
	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;
	float m_fRotX;
	float m_fRotY;
	float m_fRotZ;
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;
	CString m_objectTag;
	afx_msg void OnObjectTag();
	CString m_SelectName;
	
	float m_rPosX;
	float m_rPosY;
	float m_rPosZ;

	float m_rRotX;
	float m_rRotY;
	float m_rRotZ;

	float m_rScaleX;
	float m_rScaleZ;
	float m_rScaleY;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedClear();
	afx_msg void OnNMCustomdrawRotslider(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_SliderControlX;
	CSliderCtrl m_SliderControlY;
	CSliderCtrl m_SliderControlZ;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	CEdit m_UVScaleX;
	CEdit m_UVScaleY;
	CButton m_ColliderExistence;
};
