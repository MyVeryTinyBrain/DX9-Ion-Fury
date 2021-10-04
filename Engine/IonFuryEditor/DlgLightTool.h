#pragma once


// DlgLightTool 대화 상자

class DlgLightTool : public CDialog
{
	DECLARE_DYNAMIC(DlgLightTool)

public:
	enum class COMBOBOX { POINTLIGNT, SPOTLIGNT, DIRECTIONALLIGNT, AMBINENTLIGHT, END};

public:
	DlgLightTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgLightTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgLightTool };
#endif

private:
	COMBOBOX m_eLight;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectLight();
	CComboBox m_comboBox;
	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;

	float m_ColorRed;
	float m_ColorGreen;
	float m_ColorBlue;
	float m_ColorAlpha;

	float m_ScaleX;
	float m_ScaleY;
	float m_ScaleZ;

	float m_DirX;
	float m_DirY;
	float m_DirZ;


};
