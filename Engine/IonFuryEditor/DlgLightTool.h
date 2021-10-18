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
	void SetListBox(const wstring& lightObjName);

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
	void InitDirectionInfo();
	CComboBox m_LT_ComboBox;

// 투명도 조절하는 함수입니다. 
private:
	CSliderCtrl m_SliderCtrl_Transparency;
	int m_nOpa;
	void SetAttr(int iOpa);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:
	void SetPos(Vec3 _mouse);
	Vec3 GetPos();
	Vec3 mouse;
public:
	CString m_LightName;
	CString m_LightType;

	//색상 세팅
	int m_ColorR;
	int m_ColorG;
	int m_ColorB;
	int m_ColorA;

	//위치 세팅
	float m_PosX;
	float m_PosY;
	float m_PosZ;

	//반지름 세팅
	afx_msg void OnEnChangeLtRadius();
	CEdit m_Radius;
	CString sPos;
	CSliderCtrl m_SliderCrtl_Radius;
	int iPos;

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
	CString sdirX;
	CString sdirY;
	CString sdirZ;

	CEdit m_DirX;
	CEdit m_DirY;
	CEdit m_DirZ;

	afx_msg void OnListBoxCtrl();
	afx_msg void OnSelectLight();
	afx_msg void OnLightName();
	afx_msg void OnEnChangeLtDirx();
	afx_msg void OnEnChangeLtDiry();
	afx_msg void OnEnChangeLtDirz();
	afx_msg void OnEnChangeColorR();
	afx_msg void OnEnChangeColorG();
	afx_msg void OnEnChangeColorB();
	afx_msg void OnEnChangeColorA();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedApplyButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedAmbinentFactorSet();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedClear();


	float m_OutSideAngle;
	float m_InsideAngleRatio;
	float m_dirx;
	float m_diry;
	float m_dirz;
	float m_ambinentFactor;
	float m_radius;

	Light* lightcom;
	afx_msg void OnEnChangeLtPosx();
	afx_msg void OnEnChangeLtPosy();
	afx_msg void OnEnChangeLtPosz();

	
public:
	void SetLTPickableObject(GameObject* gameobject = nullptr);
	void SelectObject();
	void LightClear();

	void SetName(const CString& name);
	afx_msg void OnLbnDblclkList1();


	//제이슨
public:
	void EmptyListBoxBeforeLoad();

	void JsonWrite();
	void JsonRoad();

	void SaveToJsonFormat(const Json::Value& json, string path);
	Json::Value LoadFromJsonFormat(string path);
	wstring ToWString(const string& str);
	string ToString(const wstring& wstr);
};
