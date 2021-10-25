#pragma once

class MapLoad
{
public:

	static HRESULT LoadMap(const wstring& wstrFilePath);

private:

	static void SaveToJsonFormat(const Json::Value& json, string path);

	static Json::Value LoadFromJsonFormat(string path);

	static wstring ToWString(const string& str);

	static string ToString(const wstring& wstr);
};

