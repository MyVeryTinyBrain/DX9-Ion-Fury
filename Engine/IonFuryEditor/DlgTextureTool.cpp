// DlgTextureTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgTextureTool.h"
#include "afxdialogex.h"
#include "Gizmo.h"
#include "EditorManager.h"
#include "FileInfo.h"


// DlgTextureTool 대화 상자

IMPLEMENT_DYNAMIC(DlgTextureTool, CDialog)

DlgTextureTool::DlgTextureTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgTextureTool, pParent)
{

}

DlgTextureTool::~DlgTextureTool()
{
}

void DlgTextureTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PIC, m_PictureControl);
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
}


BEGIN_MESSAGE_MAP(DlgTextureTool, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &DlgTextureTool::OnTcnSelchangeTab)
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgTextureTool::SelectImage)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgTextureTool::SetTextureToPicked)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// DlgTextureTool 메시지 처리기


BOOL DlgTextureTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	{
		TCITEM item;
		item.mask = TCIF_TEXT;
		//tab 이름 자유롭게 설정. 설정 했다면 밑에 있는 define값에 경로 수정해줘요.
		item.pszText = L"tab0";
		m_TabControl.InsertItem(0, &item);
		item.pszText = L"tab1";
		m_TabControl.InsertItem(1, &item);
		item.pszText = L"tab2";
		m_TabControl.InsertItem(2, &item);

		item.pszText = L"DragAndDrop";			//드래그 드롭 써서 이미지 호출하고 싶다면 4번탭을 사용
		m_TabControl.InsertItem(3, &item);
	}

	AddFilesToListBox(TabImagePath0, m_ListBox, true);		//텍스처에 이미지 추가
	AddFilesToListBox(TabImagePath1, m_ListBox, true);
	AddFilesToListBox(TabImagePath2, m_ListBox, true);

	for (int i = m_ListBox.GetCount(); i > 0; --i)
		m_ListBox.DeleteString(i - 1);
	AddFilesToListBox(TabImagePath0, m_ListBox, false);


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgTextureTool::OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	for (int i = m_ListBox.GetCount(); i > 0; --i)
		m_ListBox.DeleteString(i - 1);

	switch (m_TabControl.GetCurSel())
	{
	case 0:
		AddFilesToListBox(TabImagePath0, m_ListBox, false);
		break;
	case 1:
		AddFilesToListBox(TabImagePath1, m_ListBox, false);
		break;
	case 2:
		AddFilesToListBox(TabImagePath2, m_ListBox, false);
		break;
	case 3:
		for (int i = 0; i < m_Cnt; ++i)
			m_ListBox.AddString(m_DragList[i]);
		break;
	}

	*pResult = 0;
}

void DlgTextureTool::AddFilesToListBox(CString RelativePath, CListBox& ListBox, bool pushTexture)
{
	WIN32_FIND_DATAW data;

	HANDLE hFile = FindFirstFileW(RelativePath, &data);			//경로따라 첫째파일 찾아 핸들 반환
	if (hFile == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("first find file 함수 실패");
		return;
	}
	while (FindNextFileW(hFile, &data))
	{
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) &&		//파일이라면
			!(data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
		{
			ListBox.AddString(CString(data.cFileName));

			if (pushTexture)
			{
				CString FileFullPath = RelativePath;
				FileFullPath.Delete(FileFullPath.GetLength() - 1);
				FileFullPath += CString(data.cFileName);
				Texture::CreateFromFile(FileFullPath.GetString());
			}
		}
	}
	FindClose(hFile);
}

void DlgTextureTool::SelectImage()
{
	if (m_ListBox.GetCurSel() == -1)
		return;

	CString FileFullPathAndName;
	CString FileName;

	m_ListBox.GetText(m_ListBox.GetCurSel(), FileName);

	int tabIdx = m_TabControl.GetCurSel();
	switch (tabIdx)
	{
	case 0:
		FileFullPathAndName = TabImagePath0;
		FileFullPathAndName.Delete(FileFullPathAndName.GetLength() - 1);
		FileFullPathAndName += FileName.GetString();
		break;
	case 1:
		FileFullPathAndName = TabImagePath1;
		FileFullPathAndName.Delete(FileFullPathAndName.GetLength() - 1);
		FileFullPathAndName += FileName.GetString();
		break;
	case 2:
		FileFullPathAndName = TabImagePath2;
		FileFullPathAndName.Delete(FileFullPathAndName.GetLength() - 1);
		FileFullPathAndName += FileName.GetString();
		break;
	default:
		FileFullPathAndName = FileName;
		break;
	}

	m_texturePath = FileFullPathAndName;

	CRect PictureRect;
	m_PictureControl.GetWindowRect(PictureRect);	//picture control 크기 얻어오기

	CDC* dc;
	dc = m_PictureControl.GetDC();					//picture control의 DC 얻어오기

	CImage preview;
	preview.Load(FileFullPathAndName);

	preview.StretchBlt(dc->m_hDC, 0, 0, PictureRect.Width(), PictureRect.Height(), SRCCOPY); //이미지를 픽쳐 컨트롤 크기로 조정

	ReleaseDC(dc);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void DlgTextureTool::SetTextureToPicked()
{
	Gizmo* pGizmo = EditorManager::GetInstance()->GetGizmo();

	pGizmo->ChangeTextureAttachedObject(m_texturePath);
}

void DlgTextureTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_TabControl.GetCurSel() != 3)										//drag분류할 tab Index
		return;

	int iCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);			//drag한 파일개수

	TCHAR szFilePath[MAX_PATH]{};

	for (int i = 0; i < iCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		CString relativePath = FileInfo::ConvertRelativePath(szFilePath);	//상대경로

		//CString fileName = PathFindFileName(szFilePath);					//파일이름
		//TCHAR szFileName[MAX_PATH]{};
		//lstrcpy(szFileName, fileName.GetString());
		//PathRemoveExtension(szFileName);									//확장자 빼기
		//m_ListBox.AddString(szFileName);

		Texture::CreateFromFile(relativePath.GetString());
		m_ListBox.AddString(relativePath);
		m_DragList[m_Cnt] = relativePath;
		m_Cnt++;
	}

	//m_ListBoxExtra.setHorizontalExtent(100);

	CDialog::OnDropFiles(hDropInfo);
}
