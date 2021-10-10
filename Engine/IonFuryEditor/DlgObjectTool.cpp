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
DlgObjectTool::DlgObjectTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DlgObjectTool, pParent)
	, m_objectName(_T(""))
	, m_eMesh(COMBOBOX::END)
	, m_fPosX(0.f)
	, m_fPosY(0.f)
	, m_fPosZ(0.f)
	, m_fRotX(0.f)
	, m_fRotY(0.f)
	, m_fRotZ(0.f)
	, m_fScaleX(1.f)
	, m_fScaleY(1.f)
	, m_fScaleZ(1.f)
	, m_meshPath(L"")
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
END_MESSAGE_MAP()


// DlgObjectTool 메시지 처리기


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

	m_meshPath = BuiltInCubeUserMesh;

	/////////////////////////////////////////////

	m_SliderControlX.SetRange(0, 360);
	m_SliderControlX.SetPos(0);
	m_SliderControlX.SetLineSize(10);

	m_SliderControlY.SetRange(0, 360);
	m_SliderControlY.SetPos(0);
	m_SliderControlY.SetLineSize(10);

	m_SliderControlZ.SetRange(0, 360);
	m_SliderControlZ.SetPos(0);
	m_SliderControlZ.SetLineSize(10);


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

	m_eMesh = (COMBOBOX)m_comboBox.GetCurSel();


	switch (m_eMesh)
	{
	case DlgObjectTool::COMBOBOX::Cube:
		m_meshPath = BuiltInCubeUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Cyilinder:
		m_meshPath = BuiltInCyilinderUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Quad:
		m_meshPath = BuiltInQuadUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Sphere:
		m_meshPath = BuiltInSphereUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Capsule:
		m_meshPath = BuiltInCapsuleUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::RightTriangle:
		m_meshPath = BuiltInRightTriangleUserMesh;
		break;
	case DlgObjectTool::COMBOBOX::Triangle:
		m_meshPath = BuiltInTriangleUserMesh;
		break;
	default:
		break;
	}

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
		//auto obj = SceneManager::GetInstance()->GetCurrentScene()->FindGameObject(m_SelectName.GetString());
		//obj->transform->position = Vec3(m_fPosX, m_fPosY, m_fPosZ);
		//obj->transform->eulerAngle = Vec3(m_fRotX, m_fRotY, m_fRotZ);
		//obj->transform->scale = Vec3(m_fScaleX, m_fScaleY, m_fScaleZ);

		GameObject* parentObj = trans->GetGameObject();

		parentObj->SetName(m_objectName.GetString());
		parentObj->SetTag(m_objectTag.GetString());

		Pickable* pick = trans->GetGameObject()->GetComponent<Pickable>();
		GameObject* ChildObj = pick->GetChildObject();
		GameObject* ParentObj = pick->GetGameObject();

		giz->transform->position = Vec3(m_fPosX, m_fPosY, m_fPosZ);

		parentObj->transform->position = Vec3(m_fPosX, m_fPosY, m_fPosZ);
		parentObj->transform->eulerAngle = Vec3(m_fRotX, m_fRotY, m_fRotZ);
		parentObj->transform->scale = Vec3(m_fScaleX, m_fScaleY, m_fScaleZ);

		m_SelectName = m_objectName;
	}

	m_SliderControlX.SetPos(0);
	m_SliderControlY.SetPos(0);
	m_SliderControlZ.SetPos(0);

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
		DWORD dwStrByte3 = 0;
		DWORD dwStrByte4 = 0;
		CString strMesh = L"";
		CString tex = L"";

		auto pickObj = Pickable::g_PickableVec;


		for (auto& pick : pickObj)
		{
			auto obj = pick->GetGameObject();

			dwStrByte = sizeof(wchar_t) * (obj->name.length() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, obj->name.c_str(), dwStrByte, &dwByte, nullptr);				// 이름

			dwStrByte2 = sizeof(wchar_t) * (obj->tag.length() + 1);
			WriteFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, obj->tag.c_str(), dwStrByte2, &dwByte, nullptr);				// tag
			
			auto meshrenderer = pick->GetRenderer();
			strMesh = meshrenderer->userMesh->GetLocalPath().c_str();
			
			dwStrByte3 = sizeof(wchar_t) * (strMesh.GetLength() + 1);
			WriteFile(hFile, &dwStrByte3, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, strMesh, dwStrByte3, &dwByte, nullptr);				// mesh
			
			auto texture = meshrenderer->GetTexture(0);
			tex = texture->GetLocalPath().c_str();

			dwStrByte4 = sizeof(wchar_t) * (tex.GetLength() + 1);
			WriteFile(hFile, &dwStrByte4, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, tex, dwStrByte4, &dwByte, nullptr);				// texture


			WriteFile(hFile, &obj->transform->position, sizeof(Vec3), &dwByte, nullptr);	// pos
			WriteFile(hFile, &obj->transform->scale, sizeof(Vec3), &dwByte, nullptr);		// scale
			WriteFile(hFile, &obj->transform->eulerAngle, sizeof(Vec3), &dwByte, nullptr);	// angle

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
		int vecSize = Pickable::g_PickableVec.size();
		for (int i = 0; i < vecSize; ++i)
		{
			Pickable::g_PickableVec[0]->gameObject->Destroy();
		}
		//

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		DWORD dwStrByte2 = 0;
		DWORD dwStrByte3 = 0;
		DWORD dwStrByte4 = 0;

		wchar_t* pBuff = nullptr;
		wchar_t* pBuff2 = nullptr;
		wchar_t* pBuff3 = nullptr;
		wchar_t* pBuff4 = nullptr;

		GameObject* pObj = nullptr;
		Vec3 vPos = {};
		Vec3 vScale = {};
		Vec3 vRot = {};

	
		while (true)
		{
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);		// 이름
			pBuff = new wchar_t[dwStrByte];
			ReadFile(hFile, pBuff, dwStrByte, &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);		// tag
			pBuff2 = new wchar_t[dwStrByte2];
			ReadFile(hFile, pBuff2, dwStrByte2, &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte3, sizeof(DWORD), &dwByte, nullptr);		// mesh
			pBuff3 = new wchar_t[dwStrByte3];
			ReadFile(hFile, pBuff3, dwStrByte3, &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte4, sizeof(DWORD), &dwByte, nullptr);		// texture
			pBuff4 = new wchar_t[dwStrByte4];
			ReadFile(hFile, pBuff4, dwStrByte4, &dwByte, nullptr);

			if (0 == dwByte)
			{
				SafeDeleteArray(pBuff);
				SafeDeleteArray(pBuff2);
				SafeDeleteArray(pBuff3);
				SafeDeleteArray(pBuff4);
				break;
			}

			pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(pBuff2);
			pObj->name = pBuff;

			Pickable* pick = pObj->AddComponent<Pickable>();
			pick->Settings(pBuff3, pBuff4);

			SafeDeleteArray(pBuff);
			SafeDeleteArray(pBuff2);
			SafeDeleteArray(pBuff3);
			SafeDeleteArray(pBuff4);

			ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);			// pos
			ReadFile(hFile, &vScale, sizeof(Vec3), &dwByte, nullptr);		// scale
			ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);			// angle

			pObj->transform->position = vPos;
			pObj->transform->scale = vScale;
			pObj->transform->eulerAngle = vRot;
		}

		CloseHandle(hFile);
	}

}

void DlgObjectTool::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_objectName = L"";

	m_fPosX = 0.f;
	m_fPosY = 0.f;
	m_fPosZ = 0.f;

	m_fScaleX = 1.f;
	m_fScaleY = 1.f;
	m_fScaleZ = 1.f;

	m_fRotX = 0.f;
	m_fRotY = 0.f;
	m_fRotZ = 0.f;

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

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	Gizmo* giz = EditorManager::GetInstance()->GetGizmo();
	if (!giz->GetSelectedObject())
		return;

	if (IDC_RotSlider == pScrollBar->GetDlgCtrlID())
	{
		m_fRotX = m_SliderControlX.GetPos();
		giz->GetGameObject()->transform->SetEulerAngle(Vec3(m_fRotX, 0, 0));
	}
	else if (IDC_RotSlider2 == pScrollBar->GetDlgCtrlID())
	{
		m_fRotY = m_SliderControlY.GetPos();
		giz->GetGameObject()->transform->SetEulerAngle(Vec3(m_fRotY, 0, 0));
	}
	else if (IDC_RotSlider3 == pScrollBar->GetDlgCtrlID())
	{
		m_fRotZ = m_SliderControlZ.GetPos();
		giz->GetGameObject()->transform->SetEulerAngle(Vec3(m_fRotZ, 0, 0));
	}
}
