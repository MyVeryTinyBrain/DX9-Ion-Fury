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
	COMBOBOX m_eLTComboBox;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void SetAttr(int iOpa);
public:
	virtual BOOL OnInitDialog();
	CComboBox m_LightToolComboBox;
	afx_msg void OnLightToolComboBox();


	float m_ColorR;
	float m_ColorG;
	float m_ColorB;
	float m_ColorA; //Alpha
	float m_PosX;
	float m_PosY;
	float m_PosZ;

	float m_Radius;
	float m_DirX;
	float m_DirY;
	float m_DirZ;





	//다이아로그 꾸미는 함수 및 변수들
	/////////////////////////////////////////////
	////배경색 설정하는 코드입니다.
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	//창 투명도 설정하는 코드 입니다. 
	CSliderCtrl m_TransparencyCtrl;
	int m_nOpa;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	/////////////////////////////////////////////
};
