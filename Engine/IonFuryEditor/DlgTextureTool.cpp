// DlgTextureTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgTextureTool.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(DlgTextureTool, CDialog)
END_MESSAGE_MAP()


// DlgTextureTool 메시지 처리기
