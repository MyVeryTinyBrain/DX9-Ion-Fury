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
	, ABCMEMBER(FALSE)
{

}

DlgLightTool::~DlgLightTool()
{
}

void DlgLightTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, ABC, ABCMEMBER);
}


BEGIN_MESSAGE_MAP(DlgLightTool, CDialog)
	ON_BN_CLICKED(mian, &DlgLightTool::lighttooltouchtouchyeasbays)
END_MESSAGE_MAP()


// DlgLightTool 메시지 처리기


void DlgLightTool::lighttooltouchtouchyeasbays()
{
	int i = 8;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
