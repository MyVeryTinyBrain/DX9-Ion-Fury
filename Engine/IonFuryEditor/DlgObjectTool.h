#pragma once


// DlgObjectTool 대화 상자

class DlgObjectTool : public CDialog
{
	DECLARE_DYNAMIC(DlgObjectTool)

public:
	enum class COMBOBOX { Cube, Cyilinder, Quad, Sphere, Capsule, RightTriangle, Triangle,  END};

public:
	void SetPickableObject(GameObject* gameobject);



public:
	DlgObjectTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgObjectTool };
#endif

private:
	COMBOBOX m_eMesh;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboBox;
	virtual BOOL OnInitDialog();
	CString m_objectName;
	CString m_meshPath;
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
	afx_msg void OnEnChangeEditPosX();
	CString m_objectTag;
	afx_msg void OnObjectTag();

	CString m_SelectName;
	BOOL m_btest;
};
