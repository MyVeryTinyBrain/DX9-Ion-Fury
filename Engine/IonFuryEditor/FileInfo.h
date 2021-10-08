#pragma once
class FileInfo
{
public:
	FileInfo();
	~FileInfo();

public:
	static CString ConvertRelativePath(CString wstrFileFullPath);
};