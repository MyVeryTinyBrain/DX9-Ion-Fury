#include "shared_stdafx.h"
#include "LightLoad.h"

#include <fstream>
#include <atlconv.h>
#include <iostream>

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

		pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject();
		pObj->name = pBuff;
		pObj->tag = pBuff2;

		SafeDeleteArray(pBuff);
		SafeDeleteArray(pBuff2);

		if (pObj->tag == L"Point")
		{
			ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);					// pos
			ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);					// rotation
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);		// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);				// color
			ReadFile(hFile, &frange, sizeof(float), &dwByte, nullptr);				// range
		}

		else if (pObj->tag == L"Spot")
		{
			ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);					// pos
			ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);					// rotation
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);		// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);				// color
			ReadFile(hFile, &frange, sizeof(float), &dwByte, nullptr);				// range
			ReadFile(hFile, &_outsideAngle, sizeof(float), &dwByte, nullptr);		// >outsideAngle 
			ReadFile(hFile, &_insideAngleRatio, sizeof(float), &dwByte, nullptr);	// >insideAngleRatio 
		}


		else if (pObj->tag == L"Directional")
		{
			ReadFile(hFile, &vPos, sizeof(Vec3), &dwByte, nullptr);					// pos
			ReadFile(hFile, &vRot, sizeof(Vec3), &dwByte, nullptr);					// rotation
			ReadFile(hFile, &fambinentfactor, sizeof(float), &dwByte, nullptr);		// ambinentfactor
			ReadFile(hFile, &Vcolor, sizeof(Vec4), &dwByte, nullptr);				// color
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		if (pObj->tag == L"Point")
		{
			pObj->transform->position = vPos;
			pObj->transform->eulerAngle = vRot;
			PointLight* point = pObj->AddComponent<PointLight>();

			point->ambientFactor = fambinentfactor;
			point->color = Vcolor;
			point->range = frange;
		}

		else if (pObj->tag == L"Spot")
		{
			pObj->transform->position = vPos;
			pObj->transform->eulerAngle = vRot;
			SpotLight* spot = pObj->AddComponent<SpotLight>();

			spot->ambientFactor = fambinentfactor;
			spot->color = Vcolor;
			spot->range = frange;
			spot->outsideAngle = _outsideAngle;
			spot->insideAngleRatio = _insideAngleRatio;

		}

		else if (pObj->tag == L"Directional")
		{
			pObj->transform->position = vPos;
			pObj->transform->eulerAngle = vRot;
			auto directional = pObj->AddComponent<DirectionalLight>();

			directional->ambientFactor = fambinentfactor;
			directional->color = Vcolor;
		}
	}

	CloseHandle(hFile);

	return S_OK;
}

void LightLoad::LightObjectLoadJson(const wstring& wstrFilePath)
{
	Json::Value root;
	std::ifstream ifs;
	ifs.open(wstrFilePath);

	if (!ifs.is_open())
	{
		MessageBox(nullptr, L"Load failed: faield to parse json", L"Failed Load", MB_OK | MB_ICONSTOP);
		return ;
	}

	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs))
	{
		ifs.close();
		MessageBox(nullptr, L"Load failed: faield to parse json", L"Failed Load", MB_OK | MB_ICONSTOP);
		return ;
	}

	auto to_wstring = [](const string& str)
	{
		USES_CONVERSION;
		return wstring(A2W(str.c_str()));
	};

	GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject();
	float Range = 0.f;
	float OutsideAngle = 0.f;
	float InsideAngleRatio = 0.f;

	for (Json::ArrayIndex i = 0; i < root.size(); ++i)
	{

		Json::Value Light = root[i];
		//	Json::Value LightValue = Light[i];
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

		GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject();
		pObj->name = Name;
		pObj->tag = Tag;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		pObj->transform->position = Pos;
		pObj->transform->eulerAngle = EulerAngle;

		if (Tag == L"Point")
		{
			PointLight* point = pObj->AddComponent<PointLight>();

			point->ambientFactor = AmbinentFactor;
			point->color = VColor;
			point->range = Range;
		}
		else if (Tag == L"Spot")
		{
			SpotLight* spot = pObj->AddComponent<SpotLight>();

			spot->ambientFactor = AmbinentFactor;
			spot->color = VColor;
			spot->range = Range;
			spot->outsideAngle = OutsideAngle;
			spot->insideAngleRatio = InsideAngleRatio;
		}
		else if (Tag == L"Directional")
		{
			DirectionalLight* directional = pObj->AddComponent<DirectionalLight>();

			directional->ambientFactor = AmbinentFactor;
			directional->color = VColor;
		}
	}

	ifs.close();

	//MessageBox(nullptr, L"Load complete", L"Success Load", MB_OK );
}

Json::Value LightLoad::LoadFromJsonFormat(string path)
{
	std::ifstream in;
	in.open(path);

	if (!in.is_open())
	{
		cout << "json read error: not exist file" << endl;
		return Json::Value();
	}

	in.seekg(0, std::ios::end);
	size_t size = (size_t)in.tellg();
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

wstring LightLoad::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string LightLoad::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
}
