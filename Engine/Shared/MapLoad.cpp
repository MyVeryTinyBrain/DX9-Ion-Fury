#include "shared_stdafx.h"
#include "MapLoad.h"
#include "MapObject.h"

#include <fstream>
#include <atlconv.h>

HRESULT MapLoad::LoadMap(const wstring& wstrFilePath)
{
	Json::Value root = LoadFromJsonFormat(ToString(wstrFilePath));
	int RootSize = (int)root.size();

	for (int i = 0; i < RootSize; ++i)
	{
		//MapObj
		Json::Value MapValue = root[i];

		wstring Name = ToWString(MapValue["Name"].asString());
		wstring Tag = ToWString(MapValue["Tag"].asString());
		wstring TexturePath = ToWString(MapValue["TexturePath"].asString());
		int iMeshType = MapValue["MeshType"].asInt();

		Vec3 Pos = Vec3(MapValue["PositionX"].asFloat(), MapValue["PositionY"].asFloat(), MapValue["PositionZ"].asFloat());
		Vec3 Scale = Vec3(MapValue["ScaleX"].asFloat(), MapValue["ScaleY"].asFloat(), MapValue["ScaleZ"].asFloat());
		Vec3 EulerAngle = Vec3(MapValue["RotationX"].asFloat(), MapValue["RotationY"].asFloat(), MapValue["RotationZ"].asFloat());

		Vec2 UVScale = Vec2(MapValue["UVScaleX"].asFloat(), MapValue["UVScaleY"].asFloat());
		bool ColliderExistence = MapValue["ColliderExistence"].asBool();
		wstring materialType = ToWString(MapValue["MaterialType"].asString());
		
		GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(Tag);
		pObj->name = Name;

		pObj->transform->position = Pos;
		pObj->transform->scale = Scale;
		pObj->transform->eulerAngle = EulerAngle;

		MapObject* compMapObj = pObj->AddComponent<MapObject>();
		compMapObj->InitializeMapObject(TexturePath, materialType, UVScale, iMeshType, ColliderExistence);
	}

    return S_OK;
}

void MapLoad::SaveToJsonFormat(const Json::Value& json, string path)
{
	Json::StreamWriterBuilder builder;
	string jsonFormatText = Json::writeString(builder, json);

	std::ofstream out;
	out.open(path);

	out << jsonFormatText;

	out.close();
}

Json::Value MapLoad::LoadFromJsonFormat(string path)
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

wstring MapLoad::ToWString(const string& str)
{
	USES_CONVERSION;
	return wstring(A2W(str.c_str()));
}

string MapLoad::ToString(const wstring& wstr)
{
	USES_CONVERSION;
	return string(W2A(wstr.c_str()));
}
