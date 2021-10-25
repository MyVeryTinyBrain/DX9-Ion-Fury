#pragma once

class Trigger;

class TotalLoad
{
	struct SharedData
	{
		wstring name;
		Vec3 position;
		Vec3 eulerAngle;
		Vec3 scale;
	};

	struct TriggerData
	{
		SharedData sd;
		int method;
		bool once;
	};

	struct EventObjectData
	{
		SharedData sd;
		int type;
	};

public:

	static HRESULT Load(const wstring& wstrFilePath);

	static void EnchantComponent(GameObject* pObj, const wstring& ComponentType);

	static Trigger* CreateTrigger(const TriggerData& data);

	static Component* CreateEventObject(const EventObjectData& data);

private:

	static HRESULT LoadFromMapData(const Json::Value& json);

	static HRESULT LoadFromTriggerEventData(const Json::Value& json);
	 
	static HRESULT LoadFromLightData(const Json::Value& json);
	 
	static HRESULT LoadFromHandleObjectData(const Json::Value& json);

private:

	static void SaveToJsonFormat(const Json::Value& json, string path);

	static Json::Value LoadFromJsonFormat(string path);

	static wstring ToWString(const string& str);

	static string ToString(const wstring& wstr);

};

