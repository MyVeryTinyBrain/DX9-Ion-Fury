
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
	ON_COMMAND(ID_32771, &CIonFuryEditorView::OnMap)
	ON_COMMAND(ID_32772, &CIonFuryEditorView::OnLight)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_32773, &CIonFuryEditorView::OnTextureTool)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Menu, &CIonFuryEditorView::OnMonsterTool)
	ON_COMMAND(ID_FILE_SAVE_AS, &CIonFuryEditorView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &CIonFuryEditorView::OnFileOpen)
	ON_COMMAND(ID_32776, &CIonFuryEditorView::OnObject)
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

	if (!m_dlgMapTool.GetSafeHwnd())
		m_dlgMapTool.Create(IDD_DlgMapTool);

	if (!m_dlgLightTool.GetSafeHwnd())
		m_dlgLightTool.Create(IDD_DlgLightTool);

	if (!m_dlgTextureTool.GetSafeHwnd())
		m_dlgTextureTool.Create(IDD_DlgTextureTool);

	//터질경우 의심해볼 코드
	if (!m_dlgMonsterTool.GetSafeHwnd())
		m_dlgMonsterTool.Create(IDD_DlgMonsterTool);

	if (!m_dlgObjectTool.GetSafeHwnd())
		m_dlgObjectTool.Create(IDD_DlgObjTool);
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


void CIonFuryEditorView::OnMap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgMapTool.GetSafeHwnd())
		m_dlgMapTool.Create(IDD_DlgMapTool);
	m_dlgMapTool.ShowWindow(SW_SHOW);
}


void CIonFuryEditorView::OnLight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgLightTool.GetSafeHwnd())
		m_dlgLightTool.Create(IDD_DlgLightTool);
	m_dlgLightTool.ShowWindow(SW_SHOW);
}

void CIonFuryEditorView::OnObject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_dlgObjectTool.GetSafeHwnd())
		m_dlgObjectTool.Create(IDD_DlgObjTool);
	m_dlgObjectTool.ShowWindow(SW_SHOW);
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
	case 46:		//delete키
		giz = EditorManager::GetInstance()->GetGizmo();
		giz->DeleteAttachedObject();
		giz->Detach();
		giz->enable = false;
		m_dlgMapTool.Clear();
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

	//========================================================================
	giz->Click();
	if (giz->PickHandle())
		return;						
	//기즈모를 가장 우선적으로 선택하도록한 어거지코드!! 문제터지면 삭제
	//========================================================================

	Pickable* pick = Pickable::Pick();

	m_dlgMonsterTool.ClearEverything();
	m_dlgMapTool.Clear();

	if (pick)
	{
		auto pickObj = pick->GetGameObject();

		if (!m_dlgMapTool)
			return;

		Type PickType = pick->GetType();

		switch (PickType)
		{
		case Type::Map:
			m_dlgMapTool.SetPickableObject(pickObj);
			m_dlgMapTool.SelectObject();
			m_dlgMapTool.UpdateUVScale(pick);
			m_dlgMapTool.ReturnComboBoxSelect(pick);
			m_dlgMapTool.ReturnCollisionExistenceSelect(pick);

			m_dlgMonsterTool.TriggerListBoxPick(-1); //mapObject를 picking한거면 trigger목록의 selection을 해제한다.
			break;
		case Type::Trigger:
			m_dlgMonsterTool.TriggerListBoxPick(pick->GetTriggerVectorIndex());
			m_dlgMonsterTool.OnLbnSelChangeTrigger();
			break;
		case Type::EventObject:
			int TriggerIndex = -1;
			int EventIndex = -1;
			pick->GetEventVectorIndex(TriggerIndex, EventIndex);
			m_dlgMonsterTool.SetTwoListBox(TriggerIndex, EventIndex);
			m_dlgMonsterTool.PickedMethodToButton(TriggerIndex);
			m_dlgMonsterTool.m_EventListBox.SetCurSel(EventIndex);
			m_dlgMonsterTool.m_EventTypeComboBox.SetCurSel((int)pick->GetEventType());
			//rotScale원래대로
			m_dlgMonsterTool.SetRotationScrollToPicked(pick);
			m_dlgMonsterTool.SetScaleScrollToPicked(pick);
			break;
		}
		return;						//pickable 대상으로 pick을 성공하면 더이상 레이캐스팅을 진행하지 않는다.
	}
	else if (!giz->PickHandle())
	{
		giz->Detach();
		giz->enable = false;
		//m_dlgObjectTool.Clear();
	}

	//=========================================================

	LightObj* light = LightObj::LightPick();
	m_dlgLightTool.LightClear();

	if (light)
	{
		auto lightobj = light->GetGameObject();

		for (auto& light : LightObj::g_vecLight)
		{

			if (lightobj)
			{
				m_dlgLightTool.SetLTPickableObject(lightobj);
			}
			else
				return;
		}
	}


	else if (!giz->PickHandle())
	{
		cout << "조명선택안됨" << endl;
		giz->Detach();
		giz->enable = false;
	}


}

void CIonFuryEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	if (!EditorManager::GetInstance())
		return;

	Gizmo* m_giz = EditorManager::GetInstance()->GetGizmo();
	if (!m_giz)
		return;

	bool Handling = m_giz->GetHandlingState();

	if (Handling)		//기즈모 잡혔다
	{
		Transform* trans = m_giz->GetSelectedObject();
		if (!trans)
			return;

		Pickable* picked = trans->GetGameObject()->GetComponent<Pickable>();

		// 1.Obj에 대해
		if (picked)
		{
			Type type = picked->GetType();

			switch (type)
			{
			case Type::Map:
				auto pickObj = trans->GetGameObject();
				m_dlgMapTool.SetPickableObject(pickObj);
				m_dlgMapTool.SelectObject();
				break;
			}
		}
		//											용섭구역
		else
		{
			auto pickObj = m_giz->GetSelectedObject()->GetGameObject();
			m_dlgLightTool.SetLTPickableObject(pickObj);
		}
		//											성연구역
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

void CIonFuryEditorView::DetachGizmo()
{
	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->Detach();
	giz->enable = false;
}

void CIonFuryEditorView::SaveToJsonFormat(const Json::Value& json, string path)
{
	Json::StreamWriterBuilder builder;
	string jsonFormatText = Json::writeString(builder, json);

	std::ofstream out;
	out.open(path);

	out << jsonFormatText;

	out.close();
}

Json::Value CIonFuryEditorView::LoadFromJsonFormat(string path)
{
	std::ifstream in;
	in.open(path);

	if (!in.is_open())
	{
		cout << "json read error: not exist file" << endl;
		return Json::Value();
	}

	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	std::string jsonFormatText(size, ' ');
	in.seekg(0);
	in.read(&jsonFormatText[0], size);

	in.close();

	Json::Value root;
	JSONCPP_STRING err;

	Json::CharReaderBuilder charReaderBuilder;
	const std::unique_ptr<Json::CharReader> reader(charReaderBuilder.newCharReader());
	if (!reader->parse(jsonFormatText.c_str(), jsonFormatText.c_str() + jsonFormatText.length(), &root, &err))
	{
		cout << "json read error: invalid format" << endl;
		return EXIT_FAILURE;
	}

	return root;
}

wstring CIonFuryEditorView::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string CIonFuryEditorView::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
}


void CIonFuryEditorView::OnFileSaveAs()
{
	//TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"txt", L"TotalData.txt", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data\\Total");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		Json::Value Root;
		Json::Value MapObjects;
		Json::Value TriggerEvents;
		Json::Value Lights;

		{
			std::vector<Pickable*> MapVec = Pickable::g_MapVec;
			for (unsigned int i = 0; i < MapVec.size(); ++i)
			{
				Pickable* MapObject = MapVec[i];

				Json::Value MapValue;
				MapValue["Name"] = ToString(MapObject->GetGameObject()->GetName());
				MapValue["Tag"] = ToString(MapObject->GetGameObject()->GetTag());
				MapValue["TexturePath"] = ToString(MapObject->GetRenderer()->GetTexture(0)->GetLocalPath());
				MapValue["MeshType"] = (int)MapObject->GetMeshType();
				MapValue["PositionX"] = MapObject->GetGameObject()->GetTransform()->position.x;
				MapValue["PositionY"] = MapObject->GetGameObject()->GetTransform()->position.y;
				MapValue["PositionZ"] = MapObject->GetGameObject()->GetTransform()->position.z;
				MapValue["ScaleX"] = MapObject->GetGameObject()->GetTransform()->scale.x;
				MapValue["ScaleY"] = MapObject->GetGameObject()->GetTransform()->scale.y;
				MapValue["ScaleZ"] = MapObject->GetGameObject()->GetTransform()->scale.z;
				MapValue["RotationX"] = MapObject->GetGameObject()->transform->eulerAngle.x;
				MapValue["RotationY"] = MapObject->GetGameObject()->transform->eulerAngle.y;
				MapValue["RotationZ"] = MapObject->GetGameObject()->transform->eulerAngle.z;
				MapValue["UVScaleX"] = MapObject->GetUserMesh()->uvScale.x;
				MapValue["UVScaleY"] = MapObject->GetUserMesh()->uvScale.y;
				MapValue["ColliderExistence"] = MapObject->GetCollisionExistence();

				MapObjects[i] = MapValue;
			}
			Root["MapObjects"] = MapObjects;
		}

		{
			std::vector<Pickable*> TriggerVec = Pickable::g_TriggerVec;
			for (unsigned int i = 0; i < TriggerVec.size(); ++i)
			{
				Pickable* TriggerObject = TriggerVec[i];

				Json::Value TriggerEvent;

				//Trigger[0] = trigger
				{
					Json::Value TriggerValue;
					TriggerValue["Name"] = ToString(TriggerObject->GetGameObject()->GetName());
					TriggerValue["PositionX"] = TriggerObject->GetGameObject()->GetTransform()->position.x;
					TriggerValue["PositionY"] = TriggerObject->GetGameObject()->GetTransform()->position.y;
					TriggerValue["PositionZ"] = TriggerObject->GetGameObject()->GetTransform()->position.z;
					TriggerValue["ScaleX"] = TriggerObject->GetGameObject()->GetTransform()->scale.x;
					TriggerValue["ScaleY"] = TriggerObject->GetGameObject()->GetTransform()->scale.y;
					TriggerValue["ScaleZ"] = TriggerObject->GetGameObject()->GetTransform()->scale.z;
					TriggerValue["RotationX"] = TriggerObject->GetGameObject()->transform->eulerAngle.x;
					TriggerValue["RotationY"] = TriggerObject->GetGameObject()->transform->eulerAngle.y;
					TriggerValue["RotationZ"] = TriggerObject->GetGameObject()->transform->eulerAngle.z;
					TriggerValue["TriggerMethod"] = (int)TriggerObject->GetTriggerMethod();
					TriggerValue["TriggerToolAutoNum"] = m_dlgMonsterTool.m_TriggerCnt; //m_TriggerCnt;

					TriggerEvent[0] = TriggerValue;
				}

				//Trigger[1~] = Event
				std::vector<Pickable*> EventVec = TriggerObject->GetEventVec();
				for (unsigned int j = 0; j < EventVec.size(); ++j)
				{
					Json::Value Event;
					Pickable* EventObject = EventVec[j];
					Event["Name"] = ToString(EventObject->GetGameObject()->GetName());
					Event["PositionX"] = EventObject->GetGameObject()->GetTransform()->position.x;
					Event["PositionY"] = EventObject->GetGameObject()->GetTransform()->position.y;
					Event["PositionZ"] = EventObject->GetGameObject()->GetTransform()->position.z;
					Event["ScaleX"] = EventObject->GetGameObject()->GetTransform()->scale.x;
					Event["ScaleY"] = EventObject->GetGameObject()->GetTransform()->scale.y;
					Event["ScaleZ"] = EventObject->GetGameObject()->GetTransform()->scale.z;
					Event["RotationX"] = EventObject->GetGameObject()->transform->eulerAngle.x;
					Event["RotationY"] = EventObject->GetGameObject()->transform->eulerAngle.y;
					Event["RotationZ"] = EventObject->GetGameObject()->transform->eulerAngle.z;
					Event["EventType"] = (int)(EventObject->GetEventType());

					TriggerEvent[j + 1] = Event;
				}

				TriggerEvents[i] = TriggerEvent;
			}
			Root["TriggerEvents"] = TriggerEvents;
		}

		{
			std::vector<LightObj*> LightVec = LightObj::g_vecLight;
			Json::Value Lights;
			for (unsigned int i = 0; i < LightVec.size(); ++i)
			{
				LightObj* LightObject = LightVec[i];
				Json::Value LightValue;

				LightValue["Name"] = ToString(LightObject->GetGameObject()->name.c_str());
				LightValue["Tag"] = ToString(LightObject->GetGameObject()->tag.c_str());

				LightValue["PosX"] = LightObject->GetGameObject()->transform->position.x;
				LightValue["PosY"] = LightObject->GetGameObject()->transform->position.y;
				LightValue["PosZ"] = LightObject->GetGameObject()->transform->position.z;

				LightValue["EulerAngleX"] = LightObject->GetGameObject()->transform->eulerAngle.x;
				LightValue["EulerAngleY"] = LightObject->GetGameObject()->transform->eulerAngle.y;
				LightValue["EulerAngleZ"] = LightObject->GetGameObject()->transform->eulerAngle.z;

				if (LightObject->GetGameObject()->tag == L"Point")							//포인트 라인트	
				{
					auto lightcom = LightObject->GetGameObject()->GetComponentInChild<PointLight>();
					LightValue["AmbinentFactor"] = lightcom->ambientFactor;
					LightValue["ColorR"] = lightcom->color.r;
					LightValue["ColorG"] = lightcom->color.g;
					LightValue["ColorB"] = lightcom->color.b;
					LightValue["ColorA"] = lightcom->color.a;

					LightValue["Range"] = lightcom->range;
				}
				else if (LightObject->GetGameObject()->tag == L"Spot")						//스포트라이트
				{
					auto lightcom = LightObject->GetGameObject()->GetComponentInChild<SpotLight>();
					LightValue["AmbinentFactor"] = lightcom->ambientFactor;
					LightValue["ColorR"] = lightcom->color.r;
					LightValue["ColorG"] = lightcom->color.g;
					LightValue["ColorB"] = lightcom->color.b;
					LightValue["ColorA"] = lightcom->color.a;

					LightValue["Range"] = lightcom->range;

					LightValue["OutsideAngle"] = lightcom->outsideAngle;
					LightValue["InsideAngleRatio"] = lightcom->insideAngleRatio;
				}
				else if (LightObject->GetGameObject()->tag == L"Directional")					//디렉셔널라이트 
				{
					auto lightcom = LightObject->GetGameObject()->GetComponentInChild<DirectionalLight>();
					LightValue["AmbinentFactor"] = lightcom->ambientFactor;
					LightValue["ColorR"] = lightcom->color.r;
					LightValue["ColorG"] = lightcom->color.g;
					LightValue["ColorB"] = lightcom->color.b;
					LightValue["ColorA"] = lightcom->color.a;
				}

				Lights[i] = LightValue;
			}
			Root["Lights"] = Lights;
		}

		SaveToJsonFormat(Root, ToString(wstrFilePath.GetString()));
	}
}


void CIonFuryEditorView::OnFileOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	{
		CFileDialog Dlg(TRUE, L"txt", L"*.txt", OFN_OVERWRITEPROMPT);

		TCHAR szFilePath[MAX_PATH]{};

		GetCurrentDirectory(MAX_PATH, szFilePath);

		PathRemoveFileSpec(szFilePath);

		lstrcat(szFilePath, L"\\Data\\Total");

		Dlg.m_ofn.lpstrInitialDir = szFilePath;

		if (IDOK == Dlg.DoModal())
		{
			Pickable::ClearMapVector();

			CString wstrFilePath = Dlg.GetPathName();

			Json::Value Root = LoadFromJsonFormat(ToString(wstrFilePath.GetString()));
			Json::Value MapObjects = Root["MapObjects"];
			Json::Value TriggerEvents = Root["TriggerEvents"];
			Json::Value	Lights = Root["Lights"];

			//Map
			{
				int MapObjectsCnt = (int)MapObjects.size();
				for (int i = 0; i < MapObjectsCnt; ++i)
				{
					//MapObj
					Json::Value MapValue = MapObjects[i];

					wstring Name = ToWString(MapValue["Name"].asString());
					wstring Tag = ToWString(MapValue["Tag"].asString());
					wstring TexturePath = ToWString(MapValue["TexturePath"].asString());
					int temp = MapValue["MeshType"].asInt();
					COMBOBOX MeshType = (COMBOBOX)temp;

					Vec3 Pos = Vec3(MapValue["PositionX"].asFloat(), MapValue["PositionY"].asFloat(), MapValue["PositionZ"].asFloat());
					Vec3 Scale = Vec3(MapValue["ScaleX"].asFloat(), MapValue["ScaleY"].asFloat(), MapValue["ScaleZ"].asFloat());
					Vec3 EulerAngle = Vec3(MapValue["RotationX"].asFloat(), MapValue["RotationY"].asFloat(), MapValue["RotationZ"].asFloat());

					Vec2 UVScale = Vec2(MapValue["UVScaleX"].asFloat(), MapValue["UVScaleY"].asFloat());
					bool ColliderExistence = MapValue["ColliderExistence"].asBool();
					//==
					GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(Tag);
					pObj->name = Name;

					Pickable* pick = pObj->AddComponent<Pickable>();
					pick->PushInVector(Type::Map);
					pick->Settings(UVScale, (COMBOBOX)MeshType, TexturePath, ColliderExistence);

					pObj->transform->position = Pos;
					pObj->transform->scale = Scale;
					pObj->transform->eulerAngle = EulerAngle;
				}
				DetachGizmo();
			}

			//trigger
			{
				m_dlgMonsterTool.EmptyBeforeLoad();

				int RootSize = (int)TriggerEvents.size();

				for (int i = 0; i < RootSize; ++i)
				{
					//Trigger
					Json::Value TriggerEvent = TriggerEvents[i];
					Json::Value TriggerValue = TriggerEvent[0];
					wstring Name = ToWString(TriggerValue["Name"].asString());
					Vec3 Pos = Vec3(TriggerValue["PositionX"].asFloat(), TriggerValue["PositionY"].asFloat(), TriggerValue["PositionZ"].asFloat());
					Vec3 Scale = Vec3(TriggerValue["ScaleX"].asFloat(), TriggerValue["ScaleY"].asFloat(), TriggerValue["ScaleZ"].asFloat());
					Vec3 EulerAngle = Vec3(TriggerValue["RotationX"].asFloat(), TriggerValue["RotationY"].asFloat(), TriggerValue["RotationZ"].asFloat());
					int temp = TriggerValue["TriggerMethod"].asInt();
					TriggerMethod method = (TriggerMethod)temp;

					Pickable* TriggerObject = m_dlgMonsterTool.AddTriggerLoadingStyle(Name, Pos, Scale, EulerAngle, method);	//트리거 로딩
					m_dlgMonsterTool.m_TriggerCnt = TriggerValue["TriggerToolAutoNum"].asInt();									//트리거 이름 자동완성 번호 셋팅


					int TriggerSize = TriggerEvent.size();
					for (int i = 1; i < TriggerSize; ++i)
					{
						Json::Value Event = TriggerEvent[i];

						wstring Name = ToWString(Event["Name"].asString());
						Vec3 Pos = Vec3(Event["PositionX"].asFloat(), Event["PositionY"].asFloat(), Event["PositionZ"].asFloat());
						Vec3 Scale = Vec3(Event["ScaleX"].asFloat(), Event["ScaleY"].asFloat(), Event["ScaleZ"].asFloat());
						Vec3 EulerAngle = Vec3(Event["RotationX"].asFloat(), Event["RotationY"].asFloat(), Event["RotationZ"].asFloat());
						int temp = Event["EventType"].asInt();
						EventType evtType = (EventType)(temp);

						m_dlgMonsterTool.AddEventLoadingStyle(TriggerObject, Name, Pos, Scale, EulerAngle, evtType);			//해당 트리거의 이벤트 로딩
					}
				}

				m_dlgMonsterTool.EmptyAfterLoad();

			}

			//light
			{
				m_dlgLightTool.EmptyListBoxBeforeLoad();

				int vecSize = LightObj::g_vecLight.size();
				for (int i = 0; i < vecSize; ++i)
				{
					LightObj::g_vecLight[0]->gameObject->Destroy();
				}

				float Range = 0.f;
				float OutsideAngle = 0.f;
				float InsideAngleRatio = 0.f;

				int LightJsonSize = (int)Lights.size();

				for (int i = 0; i < LightJsonSize; ++i)
				{
					Json::Value Light = Lights[i];
					wstring Name = ToWString(Light["Name"].asString());
					wstring Tag = ToWString(Light["Tag"].asString());

					Vec3 Pos = Vec3(Light["PosX"].asFloat(), Light["PosY"].asFloat(), Light["PosZ"].asFloat());
					Vec3 EulerAngle = Vec3(Light["EulerAngleX"].asFloat(), Light["EulerAngleY"].asFloat(), Light["EulerAngleZ"].asFloat());
					float AmbinentFactor = Light["AmbinentFactor"].asFloat();
					Vec4 VColor = Vec4((float)Light["ColorR"].asInt(), (float)Light["ColorG"].asInt(), (float)Light["ColorB"].asInt(), (float)Light["ColorA"].asInt());

					if (Tag == L"Point")
					{
						Range = Light["Range"].asFloat();
					}
					else if (Tag == L"Spot")
					{
						Range = Light["Range"].asFloat();
						OutsideAngle = Light["OutsideAngle"].asFloat();
						InsideAngleRatio = Light["InsideAngleRatio"].asFloat();
					}

					GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(Tag);
					LightObj* lightobj = pObj->AddComponent<LightObj>();
					pObj->name = Name;
					pObj->tag = Tag;
					pObj->transform->position = Pos;
					pObj->transform->eulerAngle = EulerAngle;

					if (Tag == L"Point")
					{
						PointLight* point = pObj->GetComponentInChild<PointLight>();
						point->ambientFactor = AmbinentFactor;
						point->color = VColor;
						point->range = Range;

						lightobj->LightSetting();

					}
					else if (Tag == L"Spot")
					{
						SpotLight* spot = pObj->GetComponentInChild<SpotLight>();
						spot->ambientFactor = AmbinentFactor;
						spot->color = VColor;
						spot->range = Range;
						spot->outsideAngle = OutsideAngle;
						spot->insideAngleRatio = InsideAngleRatio;

						lightobj->LightSetting();
					}
					else if (Tag == L"Directional")
					{
						DirectionalLight* spot = pObj->GetComponentInChild<DirectionalLight>();
						spot->ambientFactor = AmbinentFactor;
						spot->color = VColor;

						lightobj->LightSetting();
					}

					m_dlgLightTool.m_LT_ListBox.InsertString(-1, pObj->name.c_str());

				}
			}

			DetachGizmo();
		}
	}
}



