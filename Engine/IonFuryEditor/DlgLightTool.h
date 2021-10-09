#pragma once


// DlgLightTool 대화 상자

class DlgLightTool : public CDialog
{
	DECLARE_DYNAMIC(DlgLightTool)

public:
	enum class COMBOBOX { POINTLIGNT, SPOTLIGNT, DIRECTIONALLIGNT, AMBINENTLIGHT, END };

public:
	DlgLightTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgLightTool();

public:
	void SetListBox();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgLightTool };
#endif
private:
	COMBOBOX m_comboBox;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	virtual BOOL OnInitDialog();
	CComboBox m_LT_ComboBox;

// 투명도 조절하는 함수입니다. 
private:
	CSliderCtrl m_SliderCtrl_Transparency;
	int m_nOpa;
	void SetAttr(int iOpa);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:
	CString m_LightName;
	CString m_LightType;

	//색상 세팅
	float m_ColorR;
	float m_ColorG;
	float m_ColorB;
	float m_ColorA;

	//위치 세팅
	float m_PosX;
	float m_PosY;
	float m_PosZ;

	//반지름 세팅
	afx_msg void OnEnChangeLtRadius();
	CEdit m_Radius;
	CSliderCtrl m_SliderCrtl_Radius;
	int iPos;
	CString sPos;


	//방향 세팅
	CSliderCtrl m_SliderDirX;
	CSliderCtrl m_SliderDirY;

	CSliderCtrl m_SliderDirZ;

	CListBox m_LT_ListBox;

	int iPosX;
	int iPosY;
	int iPosZ;
	CString sPosX;
	CString sPosY;
	CString sPosZ;



	afx_msg void OnListBoxCtrl();
	afx_msg void OnSelectLight();
	afx_msg void OnLightName();

	CEdit m_DirX;
	CEdit m_DirY;
	CEdit m_DirZ;

	afx_msg void OnEnChangeLtDirx();
	afx_msg void OnEnChangeLtDiry();
	afx_msg void OnEnChangeLtDirz();
	afx_msg void OnEnChangeColorR();
	afx_msg void OnEnChangeColorG();
	afx_msg void OnEnChangeColorB();
	afx_msg void OnEnChangeColorA();
};
