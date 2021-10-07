#pragma once

#define TabImagePath0					L"../SharedResourced/Texture/Category0/*"
#define TabImagePath1					L"../SharedResourced/Texture/Category1/*"
#define TabImagePath2					L"../SharedResourced/Texture/Category2/*"

// DlgTextureTool 대화 상자

class DlgTextureTool : public CDialog
{
	DECLARE_DYNAMIC(DlgTextureTool)

public:
	DlgTextureTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgTextureTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgTextureTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CListBox m_ListBox;
	CStatic m_PictureControl;
	CTabCtrl m_TabControl;
public:
	CString m_texturePath = L"../SharedResourced/Texture/Category0/Dev.png";
	CString m_DragList[100];
	int		m_Cnt = 0;
public:
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void SelectImage();
	afx_msg void SetTextureToPicked();
	afx_msg void OnDropFiles(HDROP hDropInfo);
public:
	void AddFilesToListBox(CString RelativePath, CListBox& ListBox, bool pushTexture);

};
