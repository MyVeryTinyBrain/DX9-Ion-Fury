#include "stdafx.h"
#include "LightLoad.h"

ImplementStaticComponent(LightLoad);


HRESULT LightLoad::LightObjectLoad(const wstring& wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	DWORD dwStrByte = 0;
	DWORD dwStrByte2 = 0;


	wchar_t* pBuff = nullptr;
	wchar_t* pBuff2 = nullptr;


	GameObject* pObj = nullptr;

	Vec3 vPos = {};
	Vec3 vScale = {};
	Vec3 vRot = {};
	float frange = 0.f;
	Vec4 Vcolor = {};
	float fambinentfactor = 0.f;
	string tag = {};

	float _outsideAngle = 0.f;
	float _insideAngleRatio = 0.f;


	while (true)
	{
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);		// ÀÌ¸§
		pBuff = new wchar_t[dwStrByte];
		ReadFile(hFile, pBuff, dwStrByte, &dwByte, nullptr);

		ReadFile(hFile, &dwStrByte2, sizeof(DWORD), &dwByte, nullptr);		// tag
		pBuff2 = new wchar_t[dwStrByte2];
		ReadFile(hFile, pBuff2, dwStrByte2, &dwByte, nullptr);


		if (0 == dwByte)
		{
			SafeDeleteArray(pBuff);
			SafeDeleteArray(pBuff2);
			break;
		}

		pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(pBuff2);
		pObj->name = pBuff;
		pObj->tag = pBuff2;

		SafeDeleteArray(pBuff);
		SafeDeleteArray(pBuff2);

		ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);				// pos
		ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);				// rotation

		if (pObj->tag == L"Point")
		{
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);	// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);			// color
			ReadFile(hFile, &frange, sizeof(float), &dwByte, nullptr);			// range
		}

		else if (pObj->tag == L"Spot")
		{
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);	// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);			// color
			ReadFile(hFile, &frange, sizeof(float), &dwByte, nullptr);			// range
			ReadFile(hFile, &_outsideAngle, sizeof(float), &dwByte, nullptr);	// >outsideAngle 
			ReadFile(hFile, &_insideAngleRatio, sizeof(float), &dwByte, nullptr);	// >insideAngleRatio 

		}


		else if (pObj->tag == L"Directional")
		{
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);	// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);			// color

		}
		//////////////////////////////////////////////////////////////////////////////

		pObj->transform->position = vPos;
		pObj->transform->eulerAngle = vRot;

		if (pObj->tag == L"Point")
		{
			PointLight* point = pObj->GetComponentInChild<PointLight>();

			point->ambientFactor = fambinentfactor;
			point->color = Vcolor;
			point->range = frange;

		}

		if (pObj->tag == L"Spot")
		{

			SpotLight* spot = pObj->GetComponentInChild<SpotLight>();


			spot->ambientFactor = fambinentfactor;
			spot->color = Vcolor;
			spot->range = frange;
			spot->outsideAngle = _outsideAngle;
			spot->insideAngleRatio = _insideAngleRatio;

		}

		if (pObj->tag == L"Directional")
		{
			DirectionalLight* directional = pObj->GetComponentInChild<DirectionalLight>();

			directional->ambientFactor = fambinentfactor;
			directional->color = Vcolor;
		}

		auto meshRendererObj = CreateGameObjectToChild(gameObject->transform);
		auto m_LightRenderer = meshRendererObj->AddComponent<UserMeshRenderer>();
		m_LightRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCyilinderUserMesh);
		m_LightRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
		meshRendererObj->transform->localEulerAngle = Vec3(90, 0, 0);
	}

	CloseHandle(hFile);

	return S_OK;
}
