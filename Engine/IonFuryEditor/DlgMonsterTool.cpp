// DlgMonsterTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgMonsterTool.h"
#include "afxdialogex.h"


// DlgMonsterTool 대화 상자

IMPLEMENT_DYNAMIC(DlgMonsterTool, CDialog)

DlgMonsterTool::DlgMonsterTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgMonsterTool, pParent)
{

}

DlgMonsterTool::~DlgMonsterTool()
{
}

void DlgMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgMonsterTool, CDialog)
END_MESSAGE_MAP()


// DlgMonsterTool 메시지 처리기
