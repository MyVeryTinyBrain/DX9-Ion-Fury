// DlgObjectTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgMapTool.h"
#include "afxdialogex.h"
#include "EditorManager.h"
#include "FreePerspectiveCamera.h"
#include "Pickable.h"
#include "Gizmo.h"
#include "EditorEnum.h"
//
#include "MainFrm.h"
#include "IonFuryEditorView.h"
#include "DlgTextureTool.h"
//
#include <fstream>
#include <atlconv.h>

// DlgObjectTool 대화 상자

IMPLEMENT_DYNAMIC(DlgMapTool, CDialog)

void DlgMapTool::SetPickableObject(GameObject* gameobject)
{
	m_SelectName = gameobject->name.c_str();
	m_objectName = gameobject->name.c_str();
	m_objectTag = gameobject->tag.c_str();

	m_rPosX = gameobject->transform->position.x;
	m_rPosY = gameobject->transform->position.y;
	m_rPosZ = gameobject->transform->position.z;

	m_rScaleX = gameobject->transform->scale.x;
	m_rScaleY = gameobject->transform->scale.y;
	m_rScaleZ = gameobject->transform->scale.z;

	m_rRotX = gameobject->transform->eulerAngle.x;
	m_rRotY = gameobject->transform->eulerAngle.y;
	m_rRotZ = gameobject->transform->eulerAngle.z;

	m_SliderControlX.SetPos((int)(gameobject->transform->eulerAngle.x + 180));
	m_SliderControlY.SetPos((int)(gameobject->transform->eulerAngle.y + 180));
	m_SliderControlZ.SetPos((int)(gameobject->transform->eulerAngle.z + 180));

	//============================
	m_SliderControlScaleX.SetPos((int)(gameobject->transform->scale.x * 10));
	m_SliderControlScaleY.SetPos((int)(gameobject->transform->scale.y * 10));
	m_SliderControlScaleZ.SetPos((int)(gameobject->transform->scale.z * 10));

	UpdateData(FALSE);
}

void DlgMapTool::SelectObject()
{
	UpdateData(TRUE);

	m_fPosX = m_rPosX;
	m_fPosY = m_rPosY;
	m_fPosZ = m_rPosZ;

	m_fScaleX = m_rScaleX;
	m_fScaleY = m_rScaleY;
	m_fScaleZ = m_rScaleZ;

	m_fRotX = m_rRotX;
	m_fRotY = m_rRotY;
	m_fRotZ = m_rRotZ;

	UpdateData(FALSE);
}

Vec3 DlgMapTool::GetToolSize()
{
	UpdateData(TRUE);
	return Vec3(m_fScaleX, m_fScaleY, m_fScaleZ);
	UpdateData(FALSE);
}

Vec3 DlgMapTool::GetToolRotation()
{
	UpdateData(TRUE);
	return Vec3(m_fRotX, m_fRotY, m_fRotZ);
	UpdateData(FALSE);
}

void DlgMapTool::Clear()
{
	UpdateData(TRUE);

	m_objectName = L"";
	m_objectTag = L"";
	m_SelectName = L"";

	m_fPosX = 0.f;			m_rPosX = 0.f;
	m_fPosY = 0.f;			m_rPosY = 0.f;
	m_fPosZ = 0.f;			m_rPosZ = 0.f;

	m_fScaleX = 1.f;		m_rScaleX = 1.f;
	m_fScaleY = 1.f;		m_rScaleY = 1.f;
	m_fScaleZ = 1.f;		m_rScaleZ = 1.f;

	m_fRotX = 0.f;			m_rRotX = 0.f;
	m_fRotY = 0.f;			m_rRotY = 0.f;
	m_fRotZ = 0.f;			m_rRotZ = 0.f;

	m_ColliderExistence.SetCheck(false);
	NumToEdit(m_UVScaleX, 1.f);
	NumToEdit(m_UVScaleY, 1.f);

	m_SliderControlX.SetPos(180);
	m_SliderControlY.SetPos(180);
	m_SliderControlZ.SetPos(180);

	m_SliderControlScaleX.SetPos(10);
	m_SliderControlScaleY.SetPos(10);
	m_SliderControlScaleZ.SetPos(10);

	m_ColliderExistence.SetCheck(true);


	UpdateData(FALSE);
}

void DlgMapTool::SaveToJsonFormat(const Json::Value& json, string path)
{
	Json::StreamWriterBuilder builder;
	string jsonFormatText = Json::writeString(builder, json);

	std::ofstream out;
	out.open(path);

	out << jsonFormatText;

	out.close();
}

Json::Value DlgMapTool::LoadFromJsonFormat(string path)
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

wstring DlgMapTool::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string DlgMapTool::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
}

DlgMapTool::DlgMapTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgMapTool, pParent)
	, m_objectName(_T(""))
	, m_fPosX(0.f)
	, m_fPosY(0.f)
	, m_fPosZ(0.f)
	, m_fRotX(0.f)
	, m_fRotY(0.f)
	, m_fRotZ(0.f)
	, m_fScaleX(1.f)
	, m_fScaleY(1.f)
	, m_fScaleZ(1.f)
	, m_MeshType(COMBOBOX::Cube)
	, m_objectTag(_T(""))
	, m_SelectName(_T(""))
	, m_rPosX(0)
	, m_rRotX(0)
	, m_rScaleX(0)
	, m_rPosY(0)
	, m_rPosZ(0)
	, m_rRotY(0)
	, m_rRotZ(0)
	, m_rScaleZ(0)
	, m_rScaleY(0)
{

}

DlgMapTool::~DlgMapTool()
{
}

void DlgMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Text(pDX, IDC_EDIT1, m_objectName);
	DDX_Text(pDX, IDC_EDIT2, m_fPosX);
	DDX_Text(pDX, IDC_EDIT3, m_fPosY);
	DDX_Text(pDX, IDC_EDIT4, m_fPosZ);
	DDX_Text(pDX, IDC_EDIT5, m_fRotX);
	DDX_Text(pDX, IDC_EDIT6, m_fRotY);
	DDX_Text(pDX, IDC_EDIT7, m_fRotZ);
	DDX_Text(pDX, IDC_EDIT8, m_fScaleX);
	DDX_Text(pDX, IDC_EDIT9, m_fScaleY);
	DDX_Text(pDX, IDC_EDIT10, m_fScaleZ);
	DDX_Text(pDX, IDC_EDIT17, m_objectTag);
	DDX_Text(pDX, OBJECT_1, m_SelectName);
	DDX_Text(pDX, OBJECT_2, m_rPosX);
	DDX_Text(pDX, OBJECT_8, m_rPosZ);
	DDX_Text(pDX, OBJECT_5, m_rPosY);
	DDX_Text(pDX, OBJECT_3, m_rRotX);
	DDX_Text(pDX, OBJECT_6, m_rRotY);
	DDX_Text(pDX, OBJECT_9, m_rRotZ);
	DDX_Text(pDX, OBJECT_4, m_rScaleX);
	DDX_Text(pDX, OBJECT_7, m_rScaleY);
	DDX_Text(pDX, OBJECT_10, m_rScaleZ);

	DDX_Control(pDX, IDC_RotSlider, m_SliderControlX);
	DDX_Control(pDX, IDC_RotSlider2, m_SliderControlY);
	DDX_Control(pDX, IDC_RotSlider3, m_SliderControlZ);


	DDX_Control(pDX, IDC_EDIT12, m_UVScaleX);
	DDX_Control(pDX, IDC_EDIT11, m_UVScaleY);
	DDX_Control(pDX, IDC_CHECK1, m_ColliderExistence);

	DDX_Control(pDX, IDC_ScaleSlider, m_SliderControlScaleX);
	DDX_Control(pDX, IDC_ScaleSlider2, m_SliderControlScaleY);
	DDX_Control(pDX, IDC_ScaleSlider3, m_SliderControlScaleZ);
	DDX_Control(pDX, IDC_RADIO3, m_ButtonGeometry);
	DDX_Control(pDX, IDC_RADIO4, m_ButtonAlphaTest);
}


BEGIN_MESSAGE_MAP(DlgMapTool, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &DlgMapTool::OnObjectName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgMapTool::OnSelectMesh)
	ON_EN_CHANGE(IDC_EDIT17, &DlgMapTool::OnObjectTag)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgMapTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON4, &DlgMapTool::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgMapTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON5, &DlgMapTool::OnBnClickedClear)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_RotSlider, &DlgMapTool::OnNMCustomdrawRotslider)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON6, &DlgMapTool::ClickAddButton)
	ON_BN_CLICKED(IDC_BUTTON7, &DlgMapTool::OnBnClickedCopyButton)
END_MESSAGE_MAP()


// DlgObjectTool 메시지 처리기


void DlgMapTool::ResetScroll()
{
	m_SliderControlX.SetPos(0);
	m_SliderControlY.SetPos(0);
	m_SliderControlZ.SetPos(0);
}

void DlgMapTool::ReturnComboBoxSelect(Pickable* pick)
{
	int sel = (int)pick->GetMeshType();
	m_comboBox.SetCurSel(sel);

	m_MeshType = (COMBOBOX)m_comboBox.GetCurSel();
}

void DlgMapTool::ReturnCollisionExistenceSelect(Pickable* pick)
{
	m_ColliderExistence.SetCheck(pick->GetCollisionExistence());
}

void DlgMapTool::ReturnGeometryOrAlphaTest(Pickable* pick)
{
	CString MaterialType = pick->GetMaterialType();
	SetCheckedButton(MaterialType);
}

void DlgMapTool::UpdateUVScale(Pickable* pick)
{
	float x = pick->GetUserMesh()->uvScale.x;
	float y = pick->GetUserMesh()->uvScale.y;

	NumToEdit(m_UVScaleX, x);
	NumToEdit(m_UVScaleY, y);
}

bool DlgMapTool::GetColliderExistence()
{
	return m_ColliderExistence.GetCheck();
}

float DlgMapTool::EditToNum(const CEdit& edit)
{
	CString str;
	edit.GetWindowTextW(str);
	wchar_t* test;
	
	return wcstof(str.GetString(), &test);
}

void DlgMapTool::NumToEdit(CEdit& edit, float num)
{
	wstring str = std::to_wstring(num);
	edit.SetWindowTextW(str.c_str());
}

CString DlgMapTool::GetCheckedButton()
{
	CString MaterialType = L"";

	int Geometry = m_ButtonGeometry.GetCheck();
	int AlphaTest = m_ButtonAlphaTest.GetCheck();

	if (Geometry)
		MaterialType = L"Geometry";
	else if (AlphaTest)
		MaterialType = L"AlphaTest";

	return MaterialType;
}

void DlgMapTool::SetCheckedButton(CString MaterialType)
{
	m_ButtonGeometry.SetCheck(0);
	m_ButtonAlphaTest.SetCheck(0);

	if (MaterialType == L"Geometry")
		m_ButtonGeometry.SetCheck(1);
	else if(MaterialType == L"AlphaTest")
		m_ButtonAlphaTest.SetCheck(1);
}

Vec2 DlgMapTool::GetToolUVScale()
{
	float x = EditToNum(m_UVScaleX);
	float y = EditToNum(m_UVScaleY);

	return Vec2(x,y);
}

BOOL DlgMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_comboBox.AddString(_T("Cube"));
	m_comboBox.AddString(_T("Cyilinder"));
	m_comboBox.AddString(_T("Quad"));
	m_comboBox.AddString(_T("Sphere"));
	m_comboBox.AddString(_T("Capsule"));
	m_comboBox.AddString(_T("RightTriangle"));
	m_comboBox.AddString(_T("Triangle"));

	m_comboBox.SetCurSel(0);
	m_ColliderExistence.SetCheck(false);
	m_MeshType = COMBOBOX::Cube;
	{
		m_SliderControlX.SetRange(0, 360);
		m_SliderControlX.SetPos(180);
		m_SliderControlX.SetLineSize(10);

		m_SliderControlY.SetRange(0, 360);
		m_SliderControlY.SetPos(180);
		m_SliderControlY.SetLineSize(10);

		m_SliderControlZ.SetRange(0, 360);
		m_SliderControlZ.SetPos(180);
		m_SliderControlZ.SetLineSize(10);
	}
	//작업중여기
	{
		m_SliderControlScaleX.SetRange(0, 200);
		m_SliderControlScaleX.SetPos(10);
		m_SliderControlScaleX.SetLineSize(10);

		m_SliderControlScaleY.SetRange(0, 200);
		m_SliderControlScaleY.SetPos(10);
		m_SliderControlScaleY.SetLineSize(10);

		m_SliderControlScaleZ.SetRange(0, 200);
		m_SliderControlScaleZ.SetPos(10);
		m_SliderControlScaleZ.SetLineSize(10);
	}
	NumToEdit(m_UVScaleX, 1.f);
	NumToEdit(m_UVScaleY, 1.f);

	m_ColliderExistence.SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgMapTool::OnObjectName()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}


void DlgMapTool::OnSelectMesh()
{
	UpdateData(TRUE);

	m_MeshType = (COMBOBOX)m_comboBox.GetCurSel();

	UpdateData(FALSE);

}

void DlgMapTool::OnObjectTag()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}

void DlgMapTool::OnBnClickedApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	auto trans = giz->GetSelectedObject();

	if (trans)
	{
		GameObject* parentObj = trans->GetGameObject();

		Pickable* pick = parentObj->GetComponent<Pickable>();

		if (!pick)
			return;
		if (pick->GetType() != Type::Map)
			return;

		parentObj->SetName(m_objectName.GetString());
		parentObj->SetTag(m_objectTag.GetString());

		giz->transform->position = Vec3(m_fPosX, m_fPosY, m_fPosZ);

		parentObj->transform->position = Vec3(m_fPosX, m_fPosY, m_fPosZ);
		parentObj->transform->eulerAngle = Vec3(m_fRotX, m_fRotY, m_fRotZ);
		parentObj->transform->scale = Vec3(m_fScaleX, m_fScaleY, m_fScaleZ);

		m_SelectName = m_objectName;
		
		//////////////////////////////////////////////////////////////////////
		
		pick->SetMesh(m_MeshType);

		float X = EditToNum(m_UVScaleX);
		float Y = EditToNum(m_UVScaleY);
		pick->GetUserMesh()->SetUVScale(Vec2(X, Y));
		pick->SetCollisionExistence(m_ColliderExistence.GetCheck());

		SetPickableObject(trans->GetGameObject());

		//////////////////////////////////////////////////////////////////////
		pick->SetMaterialTypeAs(GetCheckedButton());
	}

	//SetPickableObject(trans->GetGameObject());

	UpdateData(FALSE);
}

void DlgMapTool::OnBnClickedSave()
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CFileDialog Dlg(FALSE, L"txt", L"MapData.txt", OFN_OVERWRITEPROMPT);

		TCHAR szFilePath[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, szFilePath);

		PathRemoveFileSpec(szFilePath);

		lstrcat(szFilePath, L"\\Data\\Map");

		Dlg.m_ofn.lpstrInitialDir = szFilePath;

		if (IDOK == Dlg.DoModal())
		{
			CString wstrFilePath = Dlg.GetPathName();
			Json::Value Root;

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
				MapValue["MaterialType"] = ToString(MapObject->GetMaterialType().GetString());

				Root[i] = MapValue;
			}

			SaveToJsonFormat(Root, ToString(wstrFilePath.GetString()));
		}
	}
	return;
}

void DlgMapTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	{
		CFileDialog Dlg(TRUE, L"txt", L"*.txt", OFN_OVERWRITEPROMPT);

		TCHAR szFilePath[MAX_PATH]{};

		GetCurrentDirectory(MAX_PATH, szFilePath);

		PathRemoveFileSpec(szFilePath);

		lstrcat(szFilePath, L"\\Data\\Map");

		Dlg.m_ofn.lpstrInitialDir = szFilePath;

		if (IDOK == Dlg.DoModal())
		{
			Pickable::ClearMapVector();

			CString wstrFilePath = Dlg.GetPathName();

			Json::Value root = LoadFromJsonFormat(ToString(wstrFilePath.GetString()));
			int RootSize = (int)root.size();

			for (int i = 0; i < RootSize; ++i)
			{
				//MapObj
				Json::Value MapValue = root[i];

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

				wstring MaterialType = ToWString(MapValue["MaterialType"].asString());

				//==
				GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(Tag);
				pObj->name = Name;

				Pickable* pick = pObj->AddComponent<Pickable>();
				pick->PushInVector(Type::Map);
				pick->Settings(UVScale, (COMBOBOX)MeshType, TexturePath, ColliderExistence);
				pick->SetMaterialTypeAs(MaterialType.c_str());

				pObj->transform->position = Pos;
				pObj->transform->scale = Scale;
				pObj->transform->eulerAngle = EulerAngle;
			}
			Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
			giz->Detach();
			giz->enable= false;
		}
	}

	return;
}

void DlgMapTool::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	//m_objectName = L"";	이름 마찬가지

	//m_fPosX = 0.f;
	//m_fPosY = 0.f;
	//m_fPosZ = 0.f;		0,0,0으로 이동시킬일은 거의 없을거같아서 포지션은 냅둔다.

	m_fScaleX = 1.f;
	m_fScaleY = 1.f;
	m_fScaleZ = 1.f;

	m_fRotX = 0.f;
	m_fRotY = 0.f;
	m_fRotZ = 0.f;

	m_ColliderExistence.SetCheck(true);
	NumToEdit(m_UVScaleX, 1.f);
	NumToEdit(m_UVScaleY, 1.f);

	UpdateData(FALSE);
}

void DlgMapTool::OnNMCustomdrawRotslider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void DlgMapTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (!trans)
		return;
	
	Pickable* picked = trans->GetGameObject()->GetComponent<Pickable>();

	if (!picked)
		return;

	if (picked->GetType() != Type::Map)
		return;


	m_rRotX = float(m_SliderControlX.GetPos() - 180);
	m_rRotY = float(m_SliderControlY.GetPos() - 180);
	m_rRotZ = float(m_SliderControlZ.GetPos() - 180);

	giz->GetSelectedObject()->transform->SetEulerAngle(Vec3(m_rRotX, m_rRotY, m_rRotZ));

	m_fRotX = m_rRotX;
	m_fRotY = m_rRotY;
	m_fRotZ = m_rRotZ;
	//=====================================================================================
	m_rScaleX = float(m_SliderControlScaleX.GetPos() / 10.f);
	m_rScaleY = float(m_SliderControlScaleY.GetPos() / 10.f);
	m_rScaleZ = float(m_SliderControlScaleZ.GetPos() / 10.f);

	giz->GetSelectedObject()->transform->SetScale(Vec3(m_rScaleX, m_rScaleY, m_rScaleZ));

	m_fScaleX = m_rScaleX;
	m_fScaleY = m_rScaleY;
	m_fScaleZ = m_rScaleZ;

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgMapTool::ClickAddButton()
{
	CString MaterialType = GetCheckedButton();
	if (MaterialType == L"")
		return;

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CIonFuryEditorView* pView = dynamic_cast<CIonFuryEditorView*>(pMainFrame->GetActiveView());

	DlgTextureTool* textool = pView->GetTextureTool();
	CString TexturePath = textool->GetmemberTexturePathString();

	FreePerspectiveCamera* camera = EditorManager::GetInstance()->GetPerspectiveCamera();
	Pickable* pick = nullptr;
	pick = camera->Add_MapObject(
		GetColliderExistence(),
		GetToolSize(),
		GetToolRotation(),
		GetToolUVScale(),
		m_MeshType,
		m_objectTag.GetString(),
		m_objectName.GetString(),
		TexturePath.GetString());
	pick->SetMaterialTypeAs(MaterialType);


	SetPickableObject(pick->GetGameObject());
	SelectObject();
	UpdateUVScale(pick);
	ReturnComboBoxSelect(pick);
	ReturnCollisionExistenceSelect(pick);
}


void DlgMapTool::OnBnClickedCopyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;

	Pickable* Picked = trans->GetGameObject()->GetComponent<Pickable>();
	if (Picked == nullptr)
		return;

	GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject();
	pObj->name = L"Copied";

	Pickable* NewPickable = pObj->AddComponent<Pickable>();
	NewPickable->PushInVector(Type::Map);

	Vec3 Pos = trans->position;
	Vec3 Scale = trans->scale;
	Vec3 EulerAngle = trans->eulerAngle;

	Vec2 UVScale = Picked->GetUserMesh()->uvScale;
	COMBOBOX MeshType = Picked->GetMeshType();
	wstring TexturePath = Picked->GetRenderer()->GetTexture(0)->GetLocalPath();
	bool ColliderExistence = Picked->GetCollisionExistence();
	wstring MaterialType = Picked->GetMaterialType().GetString();

	NewPickable->Settings(UVScale, MeshType, TexturePath, ColliderExistence);
	NewPickable->SetMaterialTypeAs(MaterialType.c_str());

	pObj->transform->position = Pos;
	pObj->transform->scale = Scale;
	pObj->transform->eulerAngle = EulerAngle;
}
