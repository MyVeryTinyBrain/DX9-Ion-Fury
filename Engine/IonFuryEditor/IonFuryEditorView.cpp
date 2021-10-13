
// IonFuryEditorView.cpp: CIonFuryEditorView 클래스의 구현
//

#include "IonFuryEditorBase.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IonFuryEditor.h"
#endif

#include "IonFuryEditorDoc.h"
#include "IonFuryEditorView.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "Pickable.h"
#include "LightObj.h"
#include "EditorScene.h"
#include "Gizmo.h"
#include "EditorEnum.h"

#ifdef new
#undef new
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIonFuryEditorView

IMPLEMENT_DYNCREATE(CIonFuryEditorView, CView)

BEGIN_MESSAGE_MAP(CIonFuryEditorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CIonFuryEditorView::OnObject)
	ON_COMMAND(ID_32772, &CIonFuryEditorView::OnLight)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_32773, &CIonFuryEditorView::OnTextureTool)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Menu, &CIonFuryEditorView::OnMonsterTool)
END_MESSAGE_MAP()

// CIonFuryEditorView 생성/소멸

CIonFuryEditorView::CIonFuryEditorView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CIonFuryEditorView::~CIonFuryEditorView()
{
}

BOOL CIonFuryEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIonFuryEditorView 그리기

void CIonFuryEditorView::OnDraw(CDC* /*pDC*/)
{
	CIonFuryEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CIonFuryEditorView 인쇄

BOOL CIonFuryEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIonFuryEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIonFuryEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CIonFuryEditorView 진단

#ifdef _DEBUG
void CIonFuryEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CIonFuryEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIonFuryEditorDoc* CIonFuryEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIonFuryEditorDoc)));
	return (CIonFuryEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CIonFuryEditorView 메시지 처리기


void CIonFuryEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	RECT rect{};
	CIonFuryEditorView::GetWindowRect(&rect);

	// 엔진을 초기화합니다.
	engine.Initialize(m_hWnd, UINT(rect.right - rect.left), UINT(rect.bottom - rect.top), true);

	// 초기 씬을 설정합니다.
	SceneManager::ChangeScene(new EditorScene);

	// 매번 화면을 업데이트 하기 위해 타이머를 설정합니다.
	// 설정한 타이머 번호는 0번입니다.
	SetTimer(0, 0, 0);

	// 여기에서 우선 다이얼로그를 생성합니다.

	if (!m_dlgObjectTool.GetSafeHwnd())
		m_dlgObjectTool.Create(IDD_DlgObjectTool);

	if (!m_dlgLightTool.GetSafeHwnd())
		m_dlgLightTool.Create(IDD_DlgLightTool);

	if (!m_dlgTextureTool.GetSafeHwnd())
		m_dlgTextureTool.Create(IDD_DlgTextureTool);

	//터질경우 의심해볼 코드
	if (!m_dlgMonsterTool.GetSafeHwnd())
		m_dlgMonsterTool.Create(IDD_DlgMonsterTool);
}


void CIonFuryEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
}


void CIonFuryEditorView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		// 0번 타이머 틱이 오면
		// 엔진의 한 단계를 수행합니다.
	case 0:
		engine.Step();
		break;
	}

	CView::OnTimer(nIDEvent);
}


BOOL CIonFuryEditorView::DestroyWindow()
{
	// 윈도우가 파괴되기 직전에 타이머를 파괴합니다.
	KillTimer(0);
	return CView::DestroyWindow();
}


void CIonFuryEditorView::OnObject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgObjectTool.GetSafeHwnd())
		m_dlgObjectTool.Create(IDD_DlgObjectTool);
	m_dlgObjectTool.ShowWindow(SW_SHOW);
}


void CIonFuryEditorView::OnLight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgLightTool.GetSafeHwnd())
		m_dlgLightTool.Create(IDD_DlgLightTool);
	m_dlgLightTool.ShowWindow(SW_SHOW);
}


void CIonFuryEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	auto camera = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* pick = nullptr;
	Gizmo* giz = nullptr;
	switch (nChar)
	{
	//case 'P':
	//	if (!m_dlgObjectTool || !m_dlgTextureTool)
	//	{
	//		pick = camera->Add_MapObject();
	//	}
	//	else
	//	{
	//		//Pickable* pick = nullptr;
	//		pick = camera->Add_MapObject(
	//			m_dlgObjectTool.GetColliderExistence(),
	//			m_dlgObjectTool.GetToolSize(),
	//			m_dlgObjectTool.GetToolRotation(),
	//			m_dlgObjectTool.GetToolUVScale(),
	//			m_dlgObjectTool.m_MeshType,
	//			m_dlgObjectTool.m_objectTag.GetString(),
	//			m_dlgObjectTool.m_objectName.GetString(),
	//			m_dlgTextureTool.m_texturePath.GetString());
	//
	//		m_dlgObjectTool.SetPickableObject(pick->GetGameObject());
	//		m_dlgObjectTool.SelectObject();
	//		m_dlgObjectTool.UpdateUVScale(pick);
	//		m_dlgObjectTool.ReturnComboBoxSelect(pick);
	//		m_dlgObjectTool.ReturnCollisionExistenceSelect(pick);
	//	}
	//	break;
	case 46:		//delete키
		giz = EditorManager::GetInstance()->GetGizmo();
		giz->DeleteAttachedObject();
		giz->Detach();
		giz->enable = false;
		m_dlgObjectTool.Clear();
		break;
	default:
		break;
	}

}

void CIonFuryEditorView::OnTextureTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgTextureTool.GetSafeHwnd())
		m_dlgTextureTool.Create(IDD_DlgTextureTool);
	m_dlgTextureTool.ShowWindow(SW_SHOW);
}

void CIonFuryEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	Pickable* GizmoSelectPick = nullptr;															//
																									//
	if (giz->PickHandle())																			//
	{																								//
		GizmoSelectPick = giz->GetSelectedObject()->GetGameObject()->GetComponent<Pickable>();		//
	}																								//추가코드

	Pickable* pick = Pickable::Pick();

	//LightObj* LightPick = LightObj::LightPick();


	const Vec3& mouse = Vec3(point.x, point.y, 0.f);

	if (pick)
	{
		if (GizmoSelectPick)																		//
			pick = GizmoSelectPick;																	//추가코드

		auto pickObj = pick->GetGameObject();

		if (!m_dlgObjectTool)
			return;

		Type PickType = pick->GetType();
		
		switch(PickType)
		{
		case Type::Map:
			m_dlgObjectTool.SetPickableObject(pickObj);
			m_dlgObjectTool.SelectObject();
			m_dlgObjectTool.UpdateUVScale(pick);
			m_dlgObjectTool.ReturnComboBoxSelect(pick);
			m_dlgObjectTool.ReturnCollisionExistenceSelect(pick);

			m_dlgMonsterTool.TriggerListBoxPick(-1); //mapObject를 picking한거면 trigger목록의 selection을 해제한다.
			break;
		case Type::Trigger:
			m_dlgMonsterTool.TriggerListBoxPick(pick->GetTriggerVectorIndex());
		}
		return;						//pickable 대상으로 pick을 성공하면 더이상 레이캐스팅을 진행하지 않는다.
	}
	else if (!giz->PickHandle())
	{
		giz->Detach();
		giz->enable = false;
		m_dlgObjectTool.Clear();


		return;
	}

	//else if (LightPick)
	//{
	//	auto pickObj = LightPick->GetGameObject();

	//	if (!m_dlgLightTool)
	//		return;

	//	m_dlgLightTool.SetLTPickableObject(pickObj);

	//	return;
	//}



	//LightObj* light = LightObj::LightPick();
	for (auto& light : LightObj::g_vecLight)
	{
		auto lightobj = light->GetGameObject();
		if (lightobj)
		{
			m_dlgLightTool.SetPos(mouse);
		}
		else
			return;
	}

}

void CIonFuryEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	EditorManager* test = EditorManager::GetInstance();

	if (!test)
		return;

	Gizmo* m_giz = EditorManager::GetInstance()->GetGizmo();
	bool Handling = m_giz->GetHandlingState();

	if (Handling)
	{
		Transform* trans = m_giz->GetSelectedObject();

		if (!trans)
			return;

		auto pickObj = trans->GetGameObject();

		m_dlgObjectTool.SetPickableObject(pickObj);

		m_dlgObjectTool.SelectObject();

		m_dlgLightTool.SetLTPickableObject(pickObj);
	}
}


DlgTextureTool* CIonFuryEditorView::GetTextureTool()
{
	if (m_dlgTextureTool)
		return &m_dlgTextureTool;
}


void CIonFuryEditorView::OnMonsterTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgMonsterTool.GetSafeHwnd())
		m_dlgMonsterTool.Create(IDD_DlgMonsterTool);
	m_dlgMonsterTool.ShowWindow(SW_SHOW);
}
