#pragma once


// DlgObjectTool 대화 상자

class DlgObjectTool : public CDialog
{
	DECLARE_DYNAMIC(DlgObjectTool)

public:
	enum class COMBOBOX { Cube, Cyilinder, Quad, Sphere, Capsule, RightTriangle, Triangle,  END};

<<<<<<< HEAD

public:
	void SetPickableObject(GameObject* gameobject);
	void SelectObject();
=======
>>>>>>> main

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
	CString m_objectTag;
	afx_msg void OnObjectTag();
<<<<<<< HEAD
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

=======
>>>>>>> main
};
