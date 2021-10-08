#include "IonFuryEditorBase.h"
#include "FileInfo.h"

FileInfo::FileInfo()
{
}

FileInfo::~FileInfo()
{
}

CString FileInfo::ConvertRelativePath(CString wstrFileFullPath)
{
	TCHAR szRelativePath[MAX_PATH]{};

	TCHAR szCurDir[MAX_PATH]{};
	GetCurrentDirectory(MAX_PATH, szCurDir);

	PathRelativePathTo(szRelativePath, szCurDir, FILE_ATTRIBUTE_DIRECTORY, wstrFileFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
