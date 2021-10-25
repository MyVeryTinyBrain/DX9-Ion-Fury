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
#include "HandlingObject.h"
#include "Gizmo.h"
#include "EditorEnum.h"
//#include "../IonFury/"
//
#include <fstream>
#include <atlconv.h>


// DlgObjectTool 대화 상자

IMPLEMENT_DYNAMIC(DlgObjectTool, CDialog)

DlgObjectTool::DlgObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgObjTool, pParent)
	, m_Name(_T(""))
{

}

DlgObjectTool::~DlgObjectTool()
{
}

void DlgObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ObjectListBox);
	DDX_Control(pDX, IDC_SLIDER2, m_SliderScaleX);
	DDX_Control(pDX, IDC_SLIDER4, m_SliderScaleY);
	DDX_Control(pDX, IDC_SLIDER5, m_SliderScaleZ);
	DDX_Control(pDX, IDC_SLIDER3, m_SliderRotationX);
	DDX_Control(pDX, IDC_SLIDER6, m_SliderRotationY);
	DDX_Control(pDX, IDC_SLIDER11, m_SliderRotationZ);
	DDX_Control(pDX, IDC_SLIDER1, m_PivotSliderScale);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Control(pDX, IDC_COMBO1, m_TypeComboBox);
}

// DlgObjectTool 메시지 처리기

BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON17, &DlgObjectTool::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_BUTTON18, &DlgObjectTool::OnBnClickedResetType)
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST1, &DlgObjectTool::OnLbnSelchangeListBox)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgObjectTool::OnBnClickedRenameButton)
	ON_BN_CLICKED(IDC_BUTTON19, &DlgObjectTool::OnBnClickedRemove)
	ON_BN_CLICKED(IDC_BUTTON16, &DlgObjectTool::OnBnClickedResetScale)
	ON_BN_CLICKED(IDC_BUTTON10, &DlgObjectTool::OnBnClickedResetRotation)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgObjectTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &DlgObjectTool::OnBnClickedLoad)
END_MESSAGE_MAP()


void DlgObjectTool::SetScaleScrollToDefault(HandlingObject* picked)
{
	m_SliderScaleX.SetPos(20);
	m_SliderScaleY.SetPos(20);
	m_SliderScaleZ.SetPos(20);

	m_PivotSliderScale.SetPos(20);

	if (picked == nullptr)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->GetSelectedObject()->transform->SetScale(Vec3(1.f, 1.f, 1.f));
}


void DlgObjectTool::SetRotationScrollToDefault(HandlingObject* picked)
{
	m_SliderRotationX.SetPos(180);
	m_SliderRotationY.SetPos(180);
	m_SliderRotationZ.SetPos(180);

	if (picked == nullptr)
		return;

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->GetSelectedObject()->transform->SetEulerAngle(Vec3(0.f, 0.f, 0.f));
}


void DlgObjectTool::SetScaleScrollToPicked(HandlingObject* picked)
{
	Transform* PivotTransform = picked->GetPivotObject()->GetTransform();
	Transform* ChildTransform = picked->GetChildObject()->GetTransform();
	
	Vec3 Scale = ChildTransform->scale;
	float ScaleX = Scale.x * 20.f;
	float ScaleY = Scale.y * 20.f;
	float ScaleZ = Scale.z * 20.f;
	m_SliderScaleX.SetPos((int)ScaleX);
	m_SliderScaleY.SetPos((int)ScaleY);
	m_SliderScaleZ.SetPos((int)ScaleZ);

	Scale = PivotTransform->scale;
	m_PivotSliderScale.SetPos((int)(Scale.x * 20));
}


void DlgObjectTool::SetRotationScrollToPicked(HandlingObject* picked)
{
	Transform* ParentTransform = picked->GetGameObject()->GetTransform();

	Vec3 EulerAngle = ParentTransform->GetEulerAngle();

	float RotationX = EulerAngle.x + 180.f;
	float RotationY = EulerAngle.y + 180.f;
	float RotationZ = EulerAngle.z + 180.f;

	m_SliderRotationX.SetPos((int)RotationX);
	m_SliderRotationY.SetPos((int)RotationY);
	m_SliderRotationZ.SetPos((int)RotationZ);
}

void DlgObjectTool::SetComboBoxAsSelected(HandlingObject* picked)
{
	int ComponentSelect = -1;
	CString CompType = picked->GetComponentType();
	ComponentSelect = m_TypeComboBox.FindStringExact(-1, CompType);
	m_TypeComboBox.SetCurSel(ComponentSelect);
}

void DlgObjectTool::UndoToolStatus()
{
//	Transform* Selected = EditorManager::GetInstance()->GetGizmo()->GetSelectedObject();
//	if (Selected == nullptr)
//	{
		m_ObjectListBox.SetCurSel(-1);
		m_TypeComboBox.SetCurSel(-1);
		SetRotationScrollToDefault();
		SetScaleScrollToDefault();
	//	return;
	//}
	//if (Selected->GetGameObject()->GetComponent<HandlingObject>() == nullptr)
	//{
	//	m_ObjectListBox.SetCurSel(-1);
	//	m_TypeComboBox.SetCurSel(-1);
	//	SetRotationScrollToDefault();
	//	SetScaleScrollToDefault();
	//}
}

void DlgObjectTool::SaveToJsonFormat(const Json::Value& json, string path)
{
	Json::StreamWriterBuilder builder;
	string jsonFormatText = Json::writeString(builder, json);

	std::ofstream out;
	out.open(path);

	out << jsonFormatText;

	out.close();
}

Json::Value DlgObjectTool::LoadFromJsonFormat(string path)
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

wstring DlgObjectTool::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string DlgObjectTool::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
}


BOOL DlgObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	{
		m_TypeComboBox.AddString(_T("ItemBowAmmo"));
		m_TypeComboBox.AddString(_T("ItemChaingunAmmo"));
		m_TypeComboBox.AddString(_T("ItemLauncherAmmo"));
		m_TypeComboBox.AddString(_T("ItemRevolverAmmo"));
		m_TypeComboBox.AddString(_T("ItemShotgunAmmo"));
		m_TypeComboBox.AddString(_T("ItemSMGAmmo"));
		m_TypeComboBox.AddString(_T("ItemHealthPack"));

		m_TypeComboBox.AddString(_T("ItemArmor"));
		m_TypeComboBox.AddString(_T("ItemCardKey"));
		m_TypeComboBox.AddString(_T("ObjectRat"));

		m_TypeComboBox.AddString(_T("ObjectStairBlue"));
		m_TypeComboBox.AddString(_T("ObjectStairConcrete"));
		m_TypeComboBox.AddString(_T("ObjectStairWood"));

		m_TypeComboBox.AddString(_T("ObjectCarRed"));
		m_TypeComboBox.AddString(_T("ObjectCarBlue"));
		m_TypeComboBox.AddString(_T("ObjectCarBlack"));

		m_TypeComboBox.AddString(_T("ObjectVent"));

		m_TypeComboBox.AddString(_T("Player"));
	}

	{	//RotSlider 설정
		m_SliderRotationX.SetRange(0, 360);
		m_SliderRotationX.SetPos(180);
		m_SliderRotationX.SetLineSize(10);

		m_SliderRotationY.SetRange(0, 360);
		m_SliderRotationY.SetPos(180);
		m_SliderRotationY.SetLineSize(10);

		m_SliderRotationZ.SetRange(0, 360);
		m_SliderRotationZ.SetPos(180);
		m_SliderRotationZ.SetLineSize(10);
	}

	{	//ScaleSlider 설정
		m_SliderScaleX.SetRange(0, 100);
		m_SliderScaleX.SetPos(20);
		m_SliderScaleX.SetLineSize(10);

		m_SliderScaleY.SetRange(0, 100);
		m_SliderScaleY.SetPos(20);
		m_SliderScaleY.SetLineSize(10);

		m_SliderScaleZ.SetRange(0, 100);
		m_SliderScaleZ.SetPos(20);
		m_SliderScaleZ.SetLineSize(10);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgObjectTool::OnBnClickedAddButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_TypeComboBox.GetCurSel() == -1)
		return;

	HandlingObject* Obj = EditorManager::GetInstance()->GetPerspectiveCamera()->Add_HandlingObject(m_Cnt);
	++m_Cnt;
	
	UpdateData(true);
	if (m_Name != L"")
		Obj->GetGameObject()->name = m_Name.GetString();

	CString Type = L"";
	m_TypeComboBox.GetLBText(m_TypeComboBox.GetCurSel(), Type);
	Obj->AddComponentToChildObject(Type);

	wstring name = Obj->GetGameObject()->name;
	m_ObjectListBox.AddString(name.c_str());

	int i = m_ObjectListBox.GetCount();
	m_ObjectListBox.SetCurSel(i - 1);
	
	m_Name = L"";
	m_TypeComboBox.SetCurSel(-1);
	SetScaleScrollToDefault();
	SetRotationScrollToDefault();

	UpdateData(false);
}


void DlgObjectTool::OnBnClickedResetType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int TypeSelect = m_TypeComboBox.GetCurSel();
	if (TypeSelect == -1)
		return;

	int ObjSelect = m_ObjectListBox.GetCurSel();
	if (ObjSelect == -1)
		return;

	Transform* SelectedTransform = EditorManager::GetInstance()->GetGizmo()->GetSelectedObject();
	if (SelectedTransform == nullptr)
		return;
	if (SelectedTransform->GetGameObject()->GetComponent<HandlingObject>() == nullptr)
		return;

	HandlingObject* Obj = HandlingObject::g_HandlingVec[ObjSelect];

	CString Type = L"";
	m_TypeComboBox.GetLBText(TypeSelect, Type);
	Obj->RemoveChildObjectAndComponent();
	Obj->AddComponentToChildObject(Type);

	SetRotationScrollToDefault();
	m_SliderScaleX.SetPos(20);
	m_SliderScaleY.SetPos(20);
	m_SliderScaleZ.SetPos(20);
}


void DlgObjectTool::OnBnClickedRenameButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int ObjSelect = m_ObjectListBox.GetCurSel();
	if (ObjSelect == -1)
		return;

	Transform* SelectedTransform = EditorManager::GetInstance()->GetGizmo()->GetSelectedObject();
	if (SelectedTransform == nullptr)
		return;
	if (SelectedTransform->GetGameObject()->GetComponent<HandlingObject>() == nullptr)
		return;

	UpdateData(true);
	std::vector<HandlingObject*> ObjVec = HandlingObject::g_HandlingVec;
	HandlingObject* Obj = ObjVec[ObjSelect];
	Obj->GetGameObject()->name = m_Name.GetString();

	m_ObjectListBox.ResetContent();
	for (unsigned int i = 0; i < ObjVec.size(); ++i)
	{
		CString name = ObjVec[i]->GetGameObject()->name.c_str();
		m_ObjectListBox.AddString(name);
	}
	m_ObjectListBox.SetCurSel(ObjSelect);
}


void DlgObjectTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (!trans)
		return;

	HandlingObject* Picked = trans->GetGameObject()->GetComponent<HandlingObject>();

	if (!Picked)
		return;

	float ScaleX = float(m_SliderScaleX.GetPos() / 20.f);
	float ScaleY = float(m_SliderScaleY.GetPos() / 20.f);
	float ScaleZ = float(m_SliderScaleZ.GetPos() / 20.f);
	Picked->GetChildObject()->transform->scale = Vec3(ScaleX, ScaleY, ScaleZ);				//CompObj Scale
	
	float PivotScale = float(m_PivotSliderScale.GetPos() / 20.f);
	Picked->GetPivotObject()->transform->scale = Vec3(PivotScale, PivotScale, PivotScale);	//Pivot Scale

	float RotateX = float(m_SliderRotationX.GetPos() - 180);
	float RotateY = float(m_SliderRotationY.GetPos() - 180);
	float RotateZ = float(m_SliderRotationZ.GetPos() - 180);
	Picked->GetGameObject()->transform->SetEulerAngle(Vec3(RotateX, RotateY, RotateZ));		//Parent Rotation

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgObjectTool::OnLbnSelchangeListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Select = m_ObjectListBox.GetCurSel();
	if (Select == -1)
		return;

	HandlingObject* Obj = HandlingObject::g_HandlingVec[Select];

	SetComboBoxAsSelected(Obj);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();

	giz->Attach(Obj->transform);

	//ScaleRot picked값으로 scroll 변경
	SetScaleScrollToPicked(Obj);
	SetRotationScrollToPicked(Obj);
}


void DlgObjectTool::OnBnClickedRemove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Select = m_ObjectListBox.GetCurSel();
	if (Select == -1)
		return;

	std::vector<HandlingObject*> ObjVec = HandlingObject::g_HandlingVec;
	ObjVec[Select]->GetGameObject()->Destroy();

	m_ObjectListBox.DeleteString(Select);
	m_ObjectListBox.SetCurSel(-1);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	giz->Detach();
	giz->enable = false;

}


void DlgObjectTool::OnBnClickedResetScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_SliderScaleX.SetPos(20);
	m_SliderScaleY.SetPos(20);
	m_SliderScaleZ.SetPos(20);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;
	
	HandlingObject* Obj = trans->GetGameObject()->GetComponent<HandlingObject>();
	if (Obj == nullptr)
		return;

	Obj->GetChildObject()->GetTransform()->scale = Vec3(1.f, 1.f, 1.f);
}


void DlgObjectTool::OnBnClickedResetRotation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_SliderRotationX.SetPos(180);
	m_SliderRotationY.SetPos(180);
	m_SliderRotationZ.SetPos(180);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	Transform* trans = giz->GetSelectedObject();
	if (trans == nullptr)
		return;

	HandlingObject* Obj = trans->GetGameObject()->GetComponent<HandlingObject>();
	if (Obj == nullptr)
		return;

	Obj->GetGameObject()->GetTransform()->eulerAngle = Vec3(0.f, 0.f, 0.f);
}


void DlgObjectTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CFileDialog Dlg(FALSE, L"txt", L"HandlingData.txt", OFN_OVERWRITEPROMPT);

		TCHAR szFilePath[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, szFilePath);

		PathRemoveFileSpec(szFilePath);

		lstrcat(szFilePath, L"\\Data\\Handling");

		Dlg.m_ofn.lpstrInitialDir = szFilePath;

		if (IDOK == Dlg.DoModal())
		{
			CString wstrFilePath = Dlg.GetPathName();
			Json::Value Root;

			std::vector<HandlingObject*> ObjVec = HandlingObject::g_HandlingVec;
			for (unsigned int i = 0; i < ObjVec.size(); ++i)
			{
				HandlingObject* HandleObject = ObjVec[i];

				Json::Value ObjValue;
				ObjValue["Name"] = ToString(HandleObject->GetGameObject()->GetName());
				ObjValue["ComponentType"] = ToString(HandleObject->GetComponentType().GetString());
				ObjValue["PositionX"] = HandleObject->GetGameObject()->GetTransform()->position.x;
				ObjValue["PositionY"] = HandleObject->GetGameObject()->GetTransform()->position.y;
				ObjValue["PositionZ"] = HandleObject->GetGameObject()->GetTransform()->position.z;
				ObjValue["ChildScaleX"] = HandleObject->GetChildObject()->GetTransform()->scale.x;
				ObjValue["ChildScaleY"] = HandleObject->GetChildObject()->GetTransform()->scale.y;
				ObjValue["ChildScaleZ"] = HandleObject->GetChildObject()->GetTransform()->scale.z;
				ObjValue["PivotScale"] = HandleObject->GetPivotObject()->GetTransform()->scale.x;
				ObjValue["RotationX"] = HandleObject->GetGameObject()->transform->eulerAngle.x;
				ObjValue["RotationY"] = HandleObject->GetGameObject()->transform->eulerAngle.y;
				ObjValue["RotationZ"] = HandleObject->GetGameObject()->transform->eulerAngle.z;

				Root[i] = ObjValue;
			}

			SaveToJsonFormat(Root, ToString(wstrFilePath.GetString()));
		}
	}
	return;
}


void DlgObjectTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog Dlg(TRUE, L"txt", L"*.txt", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH]{};

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data\\Handling");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		std::vector<HandlingObject*> HandlingVec = HandlingObject::g_HandlingVec;
		
		{
			HandlingObject::ClearVector();
			HandlingObject::g_HandlingVec;
			
			m_ObjectListBox.ResetContent();
		}

		CString wstrFilePath = Dlg.GetPathName();

		Json::Value root = LoadFromJsonFormat(ToString(wstrFilePath.GetString()));
		int RootSize = (int)root.size();

		for (int i = 0; i < RootSize; ++i)
		{
			//MapObj
			Json::Value ObjValue = root[i];

			wstring Name = ToWString(ObjValue["Name"].asString());
			wstring ComponentType = ToWString(ObjValue["ComponentType"].asString());

			Vec3 Pos = Vec3(ObjValue["PositionX"].asFloat(), ObjValue["PositionY"].asFloat(), ObjValue["PositionZ"].asFloat());
			Vec3 ChildScale = Vec3(ObjValue["ChildScaleX"].asFloat(), ObjValue["ChildScaleY"].asFloat(), ObjValue["ChildScaleZ"].asFloat());
			Vec3 EulerAngle = Vec3(ObjValue["RotationX"].asFloat(), ObjValue["RotationY"].asFloat(), ObjValue["RotationZ"].asFloat());

			Vec3 PivotScale = Vec3(ObjValue["PivotScale"].asFloat(), ObjValue["PivotScale"].asFloat(), ObjValue["PivotScale"].asFloat());

			GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(L"HandlingObject");
			pObj->name = Name;

			pObj->transform->position = Pos;

			HandlingObject* HandleObj = pObj->AddComponent<HandlingObject>();
			HandleObj->AddComponentToChildObject(ComponentType.c_str());
			GameObject* ChildObj = HandleObj->GetChildObject();
			GameObject* PivotObj = HandleObj->GetPivotObject();

			ChildObj->transform->scale = ChildScale;
			PivotObj->transform->scale = PivotScale;

			pObj->transform->eulerAngle = EulerAngle;
		}

		HandlingVec = HandlingObject::g_HandlingVec;
		int Size = HandlingVec.size();
		for (int i = 0; i < Size; ++i)
		{
			m_ObjectListBox.AddString(HandlingVec[i]->GetGameObject()->name.c_str());
		}

		Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
		giz->Detach();
		giz->enable = false;
	}
}
