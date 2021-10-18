// DlgObjectTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "afxdialogex.h"
#include "DlgObjectTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorEnum.h"
//
#include <fstream>
#include <atlconv.h>


// DlgObjectTool 대화 상자

IMPLEMENT_DYNAMIC(DlgObjectTool, CDialog)

DlgObjectTool::DlgObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgObjTool, pParent)
{

}

DlgObjectTool::~DlgObjectTool()
{
}

// DlgObjectTool 메시지 처리기

BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON16, &DlgObjectTool::OnBnClickedButton16)
END_MESSAGE_MAP()


void DlgObjectTool::OnBnClickedButton16()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
