#pragma once

struct LightLoad
{
	static HRESULT LightObjectLoad(const wstring& wstrFilePath);

	static void LightObjectLoadJson(const wstring& wstrFilePath);

	Json::Value LoadFromJsonFormat(string path);

	static wstring ToWString(const string& str);
	static string ToString(const wstring& wstr);
};

