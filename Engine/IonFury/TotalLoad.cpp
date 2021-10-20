#include "stdafx.h"
#include "TotalLoad.h"

#include "MapObject.h"
#include <fstream>
#include <atlconv.h>

#include "ItemBowAmmo.h"
#include "ItemChaingunAmmo.h"
#include "ItemLauncherAmmo.h"
#include "ItemRevolverAmmo.h"
#include "ItemShotgunAmmo.h"
#include "ItemBowAmmo.h"
#include "ItemSMGAmmo.h"
#include "ItemHealthPack.h"
#include "ObjectStair.h"

HRESULT TotalLoad::Load(const wstring& wstrFilePath)
{
	Json::Value Root = LoadFromJsonFormat(ToString(wstrFilePath));
	Json::Value MapObjects = Root["MapObjects"];
	Json::Value TriggerEvents = Root["TriggerEvents"];
	Json::Value Lights = Root["Lights"];
	Json::Value HandleObjects = Root["HandleObjects"];

	int MapSize = (int)MapObjects.size();
	int HandleSize = (int)HandleObjects.size();

	//Map
	for (int i = 0; i < MapSize; ++i)
	{
		//MapObj
		Json::Value MapValue = MapObjects[i];

		wstring Name = ToWString(MapValue["Name"].asString());
		wstring Tag = ToWString(MapValue["Tag"].asString());
		wstring TexturePath = ToWString(MapValue["TexturePath"].asString());
		int iMeshType = MapValue["MeshType"].asInt();

		Vec3 Pos = Vec3(MapValue["PositionX"].asFloat(), MapValue["PositionY"].asFloat(), MapValue["PositionZ"].asFloat());
		Vec3 Scale = Vec3(MapValue["ScaleX"].asFloat(), MapValue["ScaleY"].asFloat(), MapValue["ScaleZ"].asFloat());
		Vec3 EulerAngle = Vec3(MapValue["RotationX"].asFloat(), MapValue["RotationY"].asFloat(), MapValue["RotationZ"].asFloat());

		Vec2 UVScale = Vec2(MapValue["UVScaleX"].asFloat(), MapValue["UVScaleY"].asFloat());
		bool ColliderExistence = MapValue["ColliderExistence"].asBool();

		GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(Tag);
		pObj->name = Name;

		pObj->transform->position = Pos;
		pObj->transform->scale = Scale;
		pObj->transform->eulerAngle = EulerAngle;

		MapObject* compMapObj = pObj->AddComponent<MapObject>();
		compMapObj->InitializeMapObject(TexturePath, UVScale, iMeshType, ColliderExistence);
	}

	//HandleSize	(tag´Â SpecialObjects)
	for (int i = 0; i < HandleSize; ++i)
	{
		Json::Value HandleValue = HandleObjects[i];
		wstring Name = ToWString(HandleValue["Name"].asString());
		wstring ComponentType = ToWString(HandleValue["ComponentType"].asString());

		Vec3 Pos = Vec3(HandleValue["PositionX"].asFloat(), HandleValue["PositionY"].asFloat(), HandleValue["PositionZ"].asFloat());
		Vec3 Scale = Vec3(HandleValue["ChildScaleX"].asFloat(), HandleValue["ChildScaleY"].asFloat(), HandleValue["ChildScaleZ"].asFloat());
		Vec3 EulerAngle = Vec3(HandleValue["RotationX"].asFloat(), HandleValue["RotationY"].asFloat(), HandleValue["RotationZ"].asFloat());

		GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(L"SpecialObjects");
		if (pObj == nullptr)
			return E_FAIL;

		pObj->name = Name;

		pObj->transform->position = Pos;
		pObj->transform->scale = Scale;
		pObj->transform->eulerAngle = EulerAngle;

		EnchantComponent(pObj, ComponentType);
	}

	return S_OK;
}

void TotalLoad::SaveToJsonFormat(const Json::Value& json, string path)
{
	Json::StreamWriterBuilder builder;
	string jsonFormatText = Json::writeString(builder, json);

	std::ofstream out;
	out.open(path);

	out << jsonFormatText;

	out.close();
}

Json::Value TotalLoad::LoadFromJsonFormat(string path)
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

wstring TotalLoad::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string TotalLoad::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
}

void TotalLoad::EnchantComponent(GameObject* pObj, const wstring& ComponentType)
{
	if (ComponentType == (L"ItemBowAmmo"))
		pObj->AddComponent<ItemBowAmmo>();
	else if (ComponentType == (L"ItemChaingunAmmo"))
		pObj->AddComponent<ItemChaingunAmmo>();
	else if (ComponentType == (L"ItemLauncherAmmo"))
		pObj->AddComponent<ItemLauncherAmmo>();
	else if (ComponentType == (L"ItemRevolverAmmo"))
		pObj->AddComponent<ItemRevolverAmmo>();
	else if (ComponentType == (L"ItemShotgunAmmo"))
		pObj->AddComponent<ItemShotgunAmmo>();
	else if (ComponentType == (L"ItemSMGAmmo"))
		pObj->AddComponent<ItemSMGAmmo>();
	else if (ComponentType == (L"ItemHealthPack"))
		pObj->AddComponent<ItemHealthPack>();
	else if (ComponentType == (L"ObjectStair"))
		pObj->AddComponent<ObjectStair>();
	else
		pObj->Destroy();
}

