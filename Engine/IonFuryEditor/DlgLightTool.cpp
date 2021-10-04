// DlgLightTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgLightTool.h"
#include "afxdialogex.h"


// DlgLightTool 대화 상자

IMPLEMENT_DYNAMIC(DlgLightTool, CDialog)

DlgLightTool::DlgLightTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgLightTool, pParent)
{

}

DlgLightTool::~DlgLightTool()
{
}

void DlgLightTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgLightTool, CDialog)
END_MESSAGE_MAP()


// DlgLightTool 메시지 처리기
