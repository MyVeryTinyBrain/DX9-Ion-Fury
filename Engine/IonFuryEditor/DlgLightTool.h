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
	afx_msg void OnLightTool_ComboBox();
	CString m_LightName;


// 투명도 조절하는 함수입니다. 
private:
	CSliderCtrl m_SliderCtrl_Transparency;
	int m_nOpa;
	void SetAttr(int iOpa);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:
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
	float m_Radius;
	CSliderCtrl m_SliderCrtl_Radius;

	//방향 세팅
	CSliderCtrl m_SliderDirX;
	CSliderCtrl m_SliderDirY;
	CSliderCtrl m_SliderDirZ;
	float m_LTDirX;
	float m_LTDirY;
	float m_LTDirZ;
};
