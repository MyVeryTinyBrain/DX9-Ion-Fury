#pragma once

class TotalLoad
{
public:

	static HRESULT Load(const wstring& wstrFilePath);

	static void EnchantComponent(GameObject* pObj, const wstring& ComponentType);

private:

	static void SaveToJsonFormat(const Json::Value& json, string path);

	static Json::Value LoadFromJsonFormat(string path);

	static wstring ToWString(const string& str);

	static string ToString(const wstring& wstr);

};

