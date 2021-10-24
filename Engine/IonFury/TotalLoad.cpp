#include "stdafx.h"
#include "TotalLoad.h"

#include "MapObject.h"
#include <fstream>
#include <atlconv.h>

#include <Trigger.h>
#include <BossTrigger.h>

#include <Tags.h>
#include <Names.h>

// Objects
#include "ItemBowAmmo.h"
#include "ItemChaingunAmmo.h"
#include "ItemLauncherAmmo.h"
#include "ItemRevolverAmmo.h"
#include "ItemShotgunAmmo.h"
#include "ItemBowAmmo.h"
#include "ItemSMGAmmo.h"
#include "ItemHealthPack.h"
#include <ItemArmor.h>
#include <ItemCardKey.h>
#include <ObjectRat.h>
#include <ObjectStairBlue.h>
#include <ObjectStairConcrete.h>
#include <ObjectStairWood.h>
#include <ObjectCarBlack.h>
#include <ObjectCarBlue.h>
#include <ObjectCarRed.h>
#include <Player.h>

#include <ObjectMiniGame.h>

#include <EditorEnum.h>

// Events
#include <ObjectAutoDoor.h>
#include <ObjectManualDoor.h>
#include <ObjectButton.h>
#include <ObjectCardScreen.h>

#include <Drone.h>
#include <BasicMutant.h>
#include <Mutant.h>
#include <MutantPoison.h>
#include <Deacon.h>
#include <Drone.h>
#include <Spider.h>
#include <Skull.h>
#include <Warmech.h>
#include <CultistArcher.h>
#include <CultistGunner.h>
#include <Liberator.h>

HRESULT TotalLoad::Load(const wstring& wstrFilePath)
{
	Json::Value Root = LoadFromJsonFormat(ToString(wstrFilePath));
	Json::Value MapObjects = Root["MapObjects"];
	Json::Value TriggerEvents = Root["TriggerEvents"];
	Json::Value Lights = Root["Lights"];
	Json::Value HandleObjects = Root["HandleObjects"];

	LoadFromMapData(MapObjects);

	LoadFromTriggerEventData(TriggerEvents);

	LoadFromLightData(Lights);

	LoadFromHandleObjectData(HandleObjects);

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
	else if (ComponentType == (L"ItemArmor"))
		pObj->AddComponent<ItemArmor>();
	else if (ComponentType == (L"ItemCardKey"))
		pObj->AddComponent<ItemCardKey>();
	else if (ComponentType == (L"ObjectRat"))
		pObj->AddComponent<ObjectRat>();
	else if (ComponentType == (L"Player"))
		pObj->AddComponent<Player>();
	else if (ComponentType == (L"ObjectStairBlue"))
		pObj->AddComponent<ObjectStairBlue>();
	else if (ComponentType == (L"ObjectStairConcrete"))
		pObj->AddComponent<ObjectStairConcrete>();
	else if (ComponentType == (L"ObjectStairWood"))
		pObj->AddComponent<ObjectStairWood>();
	else if (ComponentType == (L"ObjectCarBlack"))
		pObj->AddComponent<ObjectCarBlack>();
	else if (ComponentType == (L"ObjectCarBlue"))
		pObj->AddComponent<ObjectCarBlue>();
	else if (ComponentType == (L"ObjectCarRed"))
		pObj->AddComponent<ObjectCarRed>();

	else if (ComponentType == (L"ObjectMiniGame"))
		pObj->AddComponent<ObjectMiniGame>();

	else
		pObj->Destroy();
}

Trigger* TotalLoad::CreateTrigger(const TriggerData& data)
{
	GameObject* obj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject(L"Trigger");

	obj->name = data.sd.name;
	obj->transform->position = data.sd.position;
	obj->transform->eulerAngle = data.sd.eulerAngle;
	obj->transform->scale = data.sd.scale;

	Trigger* trigger = nullptr;

	if (obj->name != NAME_BOSS_TRIGGER)
	{
		trigger = obj->AddComponent<Trigger>();
	}
	else
	{
		trigger = obj->AddComponent<BossTrigger>();
	}

	TriggerMethod method = (TriggerMethod)data.method;

	trigger->SetMethod(method);
	trigger->SetTriggerOnce(data.once);

	return trigger;
}

Component* TotalLoad::CreateEventObject(const EventObjectData& data)
{
	GameObject* obj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject();
	obj->name = data.sd.name;
	obj->transform->position = data.sd.position;
	obj->transform->eulerAngle = data.sd.eulerAngle;
	obj->transform->scale = data.sd.scale;

	Component* comp = nullptr;

	switch ((EventType)data.type)
	{
		case EventType::ObjectAutoDoor:
			obj->tag = TAG_DOOR;
			comp = obj->AddComponent<ObjectAutoDoor>();
			break;
		case EventType::ObjectManualDoor:
			obj->tag = TAG_DOOR;
			comp = obj->AddComponent<ObjectManualDoor>();
			break;
		case EventType::ObjectButton:
			comp = obj->AddComponent<ObjectButton>();
			break;
		case EventType::ObjectCardScreen:
			comp = obj->AddComponent<ObjectCardScreen>();
			break;

			/*
			enum class EventType { BasicMutant, Mutant, PoisonMutant, CultistArcher, CultistGunner, Deacon, Drone, Liberator, Spider, Skull, Warmech, Wendigo,
	ObjectAutoDoor, ObjectManualDoor, ObjectCardScreen, ObjectButton,
	EventObjectEnd };	//추후 몬스터가 정해지면 수정
			*/

		case EventType::Mutant:
			comp = obj->AddComponent<Mutant>();
			break;
		case EventType::BasicMutant:
			comp = obj->AddComponent<BasicMutant>();
			break;
		case EventType::CultistArcher:
			comp = obj->AddComponent<CultistArcher>();
			break;
		case EventType::CultistGunner:
			comp = obj->AddComponent<CultistGunner>();
			break;
		case EventType::Deacon:
			comp = obj->AddComponent<Deacon>();
			break;
		case EventType::Drone:
			comp = obj->AddComponent<Drone>();
			break;
		case EventType::Liberator:
			comp = obj->AddComponent<Liberator>();
			break;
		case EventType::Spider:
			comp = obj->AddComponent<Spider>();
			break;
		case EventType::Skull:
			comp = obj->AddComponent<Skull>();
			break;
		case EventType::Warmech:
			comp = obj->AddComponent<Warmech>();
			break;

		default:
			obj->Destroy();
			break;
	}

	return comp;
}

HRESULT TotalLoad::LoadFromMapData(const Json::Value& json)
{
	int MapSize = json.size();

	for (int i = 0; i < MapSize; ++i)
	{
		//MapObj
		Json::Value MapValue = json[i];

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

HRESULT TotalLoad::LoadFromLightData(const Json::Value& json)
{
	auto to_wstring = [](const string& str)
	{
		USES_CONVERSION;
		return wstring(A2W(str.c_str()));
	};

	GameObject* pObj = SceneManager::GetInstance()->GetCurrentScene()->CreateGameObject();
	float Range = 0.f;
	float OutsideAngle = 0.f;
	float InsideAngleRatio = 0.f;

	for (Json::ArrayIndex i = 0; i < json.size(); ++i)
	{

		Json::Value Light = json[i];
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

	return S_OK;
}

HRESULT TotalLoad::LoadFromHandleObjectData(const Json::Value& json)
{
	int HandleSize = json.size();

	//HandleSize	(tag는 SpecialObjects)
	for (int i = 0; i < HandleSize; ++i)
	{
		Json::Value HandleValue = json[i];
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

HRESULT TotalLoad::LoadFromTriggerEventData(const Json::Value& json)
{
	auto MakeSharedData = [&](const Json::Value& data) -> SharedData
	{
		SharedData sd;
		sd.name = ToWString(data["Name"].asString());
		sd.position.x = data["PositionX"].asFloat();
		sd.position.y = data["PositionY"].asFloat();
		sd.position.z = data["PositionZ"].asFloat();
		sd.eulerAngle.x = data["RotationX"].asFloat();
		sd.eulerAngle.y = data["RotationY"].asFloat();
		sd.eulerAngle.z = data["RotationZ"].asFloat();
		sd.scale.x = data["ScaleX"].asFloat();
		sd.scale.y = data["ScaleY"].asFloat();
		sd.scale.z = data["ScaleZ"].asFloat();
		return sd;
	};

	auto MakeTriggerData = [&](const Json::Value& data) -> TriggerData
	{
		TriggerData td;
		td.sd = MakeSharedData(data);
		td.method = data["TriggerMethod"].asInt();
		td.once = data["TriggerOnce"].asBool();

		return td;
	};

	auto MakeEventObjectData = [&](const Json::Value& data) -> EventObjectData
	{
		EventObjectData eod;
		eod.sd = MakeSharedData(data);
		eod.type = data["EventType"].asInt();
		return eod;
	};

	for (Json::ArrayIndex i = 0; i < json.size(); ++i)
	{
		Json::Value innerValue = json[i];

		TriggerData td = MakeTriggerData(innerValue[0]);
		Trigger* trigger = CreateTrigger(td);

		for (Json::ArrayIndex j = 1; j < innerValue.size(); ++j)
		{
			EventObjectData eod = MakeEventObjectData(innerValue[j]);
			Component* comp = CreateEventObject(eod);

			if (!comp)
			{
				continue;
			}

			trigger->AddSubordinationComponent(comp);
		}
	}

	return S_OK;
}

