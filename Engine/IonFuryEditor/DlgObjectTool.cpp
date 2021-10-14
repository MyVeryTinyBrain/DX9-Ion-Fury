// DlgObjectTool.cpp: 구현 파일
//

#include "IonFuryEditorBase.h"
#include "IonFuryEditor.h"
#include "DlgObjectTool.h"
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

// DlgObjectTool 대화 상자

IMPLEMENT_DYNAMIC(DlgObjectTool, CDialog)

void DlgObjectTool::SetPickableObject(GameObject* gameobject)
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
	m_SliderControlScaleX.SetPos((int)(gameobject->transform->scale.x * 20));
	m_SliderControlScaleY.SetPos((int)(gameobject->transform->scale.y * 20));
	m_SliderControlScaleZ.SetPos((int)(gameobject->transform->scale.z * 20));

	UpdateData(FALSE);
}

void DlgObjectTool::SelectObject()
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

Vec3 DlgObjectTool::GetToolSize()
{
	UpdateData(TRUE);
	return Vec3(m_fScaleX, m_fScaleY, m_fScaleZ);
	UpdateData(FALSE);
}

Vec3 DlgObjectTool::GetToolRotation()
{
	UpdateData(TRUE);
	return Vec3(m_fRotX, m_fRotY, m_fRotZ);
	UpdateData(FALSE);
}

void DlgObjectTool::Clear()
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

	m_SliderControlScaleX.SetPos(20);
	m_SliderControlScaleY.SetPos(20);
	m_SliderControlScaleZ.SetPos(20);

	UpdateData(FALSE);
}

DlgObjectTool::DlgObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgObjectTool, pParent)
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

DlgObjectTool::~DlgObjectTool()
{
}

void DlgObjectTool::DoDataExchange(CDataExchange* pDX)
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
}


BEGIN_MESSAGE_MAP(DlgObjectTool, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &DlgObjectTool::OnObjectName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DlgObjectTool::OnSelectMesh)
	ON_EN_CHANGE(IDC_EDIT17, &DlgObjectTool::OnObjectTag)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgObjectTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON4, &DlgObjectTool::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgObjectTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON5, &DlgObjectTool::OnBnClickedClear)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_RotSlider, &DlgObjectTool::OnNMCustomdrawRotslider)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON6, &DlgObjectTool::ClickAddButton)
END_MESSAGE_MAP()


// DlgObjectTool 메시지 처리기


void DlgObjectTool::ResetScroll()
{
	m_SliderControlX.SetPos(0);
	m_SliderControlY.SetPos(0);
	m_SliderControlZ.SetPos(0);
}

void DlgObjectTool::ReturnComboBoxSelect(Pickable* pick)
{
	int sel = (int)pick->GetMeshType();
	m_comboBox.SetCurSel(sel);

	m_MeshType = (COMBOBOX)m_comboBox.GetCurSel();
}

void DlgObjectTool::ReturnCollisionExistenceSelect(Pickable* pick)
{
	m_ColliderExistence.SetCheck(pick->GetCollisionExistence());
}

void DlgObjectTool::UpdateUVScale(Pickable* pick)
{
	float x = pick->GetUserMesh()->uvScale.x;
	float y = pick->GetUserMesh()->uvScale.y;

	NumToEdit(m_UVScaleX, x);
	NumToEdit(m_UVScaleY, y);
}

bool DlgObjectTool::GetColliderExistence()
{
	return m_ColliderExistence.GetCheck();
}

float DlgObjectTool::EditToNum(const CEdit& edit)
{
	CString str;
	edit.GetWindowTextW(str);
	wchar_t* test;
	
	return wcstof(str.GetString(), &test);
}

void DlgObjectTool::NumToEdit(CEdit& edit, float num)
{
	wstring str = std::to_wstring(num);
	edit.SetWindowTextW(str.c_str());
}

Vec2 DlgObjectTool::GetToolUVScale()
{
	float x = EditToNum(m_UVScaleX);
	float y = EditToNum(m_UVScaleY);

	return Vec2(x,y);
}

BOOL DlgObjectTool::OnInitDialog()
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
		m_SliderControlScaleX.SetRange(0, 100);
		m_SliderControlScaleX.SetPos(20);
		m_SliderControlScaleX.SetLineSize(10);

		m_SliderControlScaleY.SetRange(0, 100);
		m_SliderControlScaleY.SetPos(20);
		m_SliderControlScaleY.SetLineSize(10);

		m_SliderControlScaleZ.SetRange(0, 100);
		m_SliderControlScaleZ.SetPos(20);
		m_SliderControlScaleZ.SetLineSize(10);
	}
	NumToEdit(m_UVScaleX, 1.f);
	NumToEdit(m_UVScaleY, 1.f);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgObjectTool::OnObjectName()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}


void DlgObjectTool::OnSelectMesh()
{
	UpdateData(TRUE);

	m_MeshType = (COMBOBOX)m_comboBox.GetCurSel();

	UpdateData(FALSE);

}

void DlgObjectTool::OnObjectTag()
{
	UpdateData(TRUE);


	UpdateData(FALSE);
}

void DlgObjectTool::OnBnClickedApply()
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
	}

	//SetPickableObject(trans->GetGameObject());

	UpdateData(FALSE);
}

void DlgObjectTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		DWORD dwStrByte2 = 0;
		DWORD dwStrByte4 = 0;
		CString tex = L"";

		auto MapObjects = Pickable::g_MapVec;


		for (auto& MapPick : MapObjects)
		{
			if (Type::Map != MapPick->GetType())
				break;

			auto obj = MapPick->GetGameObject();

			dwStrByte = sizeof(wchar_t) * (obj->name.length() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, obj->name.c_str(), dwStrByte, &dwByte, nullptr);				// 이름

			dwStrByte2 = sizeof(wchar_t) * (obj->tag.length() + 1);
			WriteFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, obj->tag.c_str(), dwStrByte2, &dwByte, nullptr);				// tag
			
			auto texture = MapPick->GetRenderer()->GetTexture(0);
			tex = texture->GetLocalPath().c_str();

			dwStrByte4 = sizeof(wchar_t) * (tex.GetLength() + 1);
			WriteFile(hFile, &dwStrByte4, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, tex, dwStrByte4, &dwByte, nullptr);							// texture

			WriteFile(hFile, &obj->transform->position, sizeof(Vec3), &dwByte, nullptr);	// pos
			WriteFile(hFile, &obj->transform->scale, sizeof(Vec3), &dwByte, nullptr);		// scale
			WriteFile(hFile, &obj->transform->eulerAngle, sizeof(Vec3), &dwByte, nullptr);	// angle

			//////////////////////////////////////////////////////////////////////////////////////////////

			UserMesh* mesh = MapPick->GetUserMesh();

			Vec2 UVScale = mesh->uvScale;
			int PickableType = (int)(MapPick->GetType());
			int MeshType = (int)(MapPick->GetMeshType());
			bool ColliderExistence = MapPick->GetCollisionExistence();

			WriteFile(hFile, &PickableType, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &UVScale, sizeof(Vec2), &dwByte, nullptr);
			WriteFile(hFile, &MeshType, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &ColliderExistence, sizeof(bool), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}

void DlgObjectTool::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_OVERWRITEPROMPT);

	TCHAR szFilePath[MAX_PATH]{};

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);

	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;
	
		// Release
		int vecSize = Pickable::g_MapVec.size();
		for (int i = 0; i < vecSize; ++i)
		{
			Pickable::g_MapVec[0]->gameObject->Destroy();
		}
		//

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		DWORD dwStrByte2 = 0;
		DWORD dwStrByte4 = 0;

		wchar_t* pBuff = nullptr;
		wchar_t* pBuff2 = nullptr;
		wchar_t* pBuff4 = nullptr;

		GameObject* pObj = nullptr;
		Vec3 vPos = {};
		Vec3 vScale = {};
		Vec3 vRot = {};

		Vec2 UVScale = {};
		int PickableType = (int)(Type::TypeEnd);
		int MeshType = (int)(COMBOBOX::END);
		bool ColliderExistence = false;
		bool warningsaway = false;			// warning문구 없애려고 반환만 받는다. 용도X
	
		while (true)
		{
			warningsaway = ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);		// 이름
			pBuff = new wchar_t[dwStrByte];
			warningsaway = ReadFile(hFile, pBuff, dwStrByte, &dwByte, nullptr);

			warningsaway = ReadFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);		// tag
			pBuff2 = new wchar_t[dwStrByte2];
			warningsaway = ReadFile(hFile, pBuff2, dwStrByte2, &dwByte, nullptr);

			warningsaway = ReadFile(hFile, &dwStrByte4, sizeof(DWORD), &dwByte, nullptr);		// texture
			pBuff4 = new wchar_t[dwStrByte4];
			warningsaway = ReadFile(hFile, pBuff4, dwStrByte4, &dwByte, nullptr);

			if (0 == dwByte)
			{
				SafeDeleteArray(pBuff);
				SafeDeleteArray(pBuff2);
				SafeDeleteArray(pBuff4);
				break;
			}

			pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(pBuff2);
			pObj->name = pBuff;

			warningsaway = ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);					// pos
			warningsaway = ReadFile(hFile, &vScale, sizeof(Vec3), &dwByte, nullptr);				// scale
			warningsaway = ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);					// angle

			warningsaway = ReadFile(hFile, &PickableType, sizeof(int), &dwByte, nullptr);			//TYPE:: map, trigger, monster
			warningsaway = ReadFile(hFile, &UVScale, sizeof(Vec2), &dwByte, nullptr);				//UVScale
			warningsaway = ReadFile(hFile, &MeshType, sizeof(int), &dwByte, nullptr);				//COMBOBOX:: cube, cylinder..
			warningsaway = ReadFile(hFile, &ColliderExistence, sizeof(bool), &dwByte, nullptr);		//colliderExistence

			Pickable* pick = pObj->AddComponent<Pickable>();
			pick->PushInVector((Type)PickableType);
			pick->Settings(UVScale, (COMBOBOX)MeshType, pBuff4, ColliderExistence);

			pObj->transform->position = vPos;
			pObj->transform->scale = vScale;
			pObj->transform->eulerAngle = vRot;

			SafeDeleteArray(pBuff);
			SafeDeleteArray(pBuff2);
			SafeDeleteArray(pBuff4);
		}

		Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
		giz->Detach();
		giz->enable = false;

		CloseHandle(hFile);
	}

}

void DlgObjectTool::OnBnClickedClear()
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

	m_ColliderExistence.SetCheck(false);
	NumToEdit(m_UVScaleX, 1.f);
	NumToEdit(m_UVScaleY, 1.f);

	UpdateData(FALSE);
}

void DlgObjectTool::OnNMCustomdrawRotslider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void DlgObjectTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
	m_rScaleX = float(m_SliderControlScaleX.GetPos() / 20.f);
	m_rScaleY = float(m_SliderControlScaleY.GetPos() / 20.f);
	m_rScaleZ = float(m_SliderControlScaleZ.GetPos() / 20.f);

	giz->GetSelectedObject()->transform->SetScale(Vec3(m_rScaleX, m_rScaleY, m_rScaleZ));

	m_fScaleX = m_rScaleX;
	m_fScaleY = m_rScaleY;
	m_fScaleZ = m_rScaleZ;

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DlgObjectTool::ClickAddButton()
{
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

	SetPickableObject(pick->GetGameObject());
	SelectObject();
	UpdateUVScale(pick);
	ReturnComboBoxSelect(pick);
	ReturnCollisionExistenceSelect(pick);
}
