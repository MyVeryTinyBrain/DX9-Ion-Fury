#include "EngineBase.h"
#include "Path.h"

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::wstring> Path::QueryFilePath(const std::wstring& directory)
{
	std::vector<std::wstring> filePathes;
	fs::path begin = directory;
	for (const fs::directory_entry& entry : fs::recursive_directory_iterator(begin))
	{
		const auto& path = entry.path();
		if (!fs::is_directory(path))
		{
			std::wstring wstrPath = path;
			std::replace(wstrPath.begin(), wstrPath.end(), L'\\', L'/');
			filePathes.push_back(wstrPath);
		}
	}

	return filePathes;
}

std::vector<std::wstring> Path::QueryFilePath(const std::wstring& directory, const std::wstring& extension)
{
	std::vector<std::wstring> filePathes;
	fs::path begin = directory;
	for (const fs::directory_entry& entry : fs::recursive_directory_iterator(begin))
	{
		const auto& path = entry.path();
		if (path.extension() == extension)
		{
			std::wstring wstrPath = path;
			std::replace(wstrPath.begin(), wstrPath.end(), L'\\', L'/');
			filePathes.push_back(wstrPath);
		}
	}

	return filePathes;
}

std::vector<std::wstring> Path::QueryFilePath(const std::wstring& directory, Path::QueryFilePathCallback* callback)
{
	std::vector<std::wstring> filePathes;
	fs::path begin = directory;
	for (const fs::directory_entry& entry : fs::recursive_directory_iterator(begin))
	{
		const auto& path = entry.path();
		const std::wstring& wstrPath = path;
		if (callback->Allow(wstrPath))
		{
			std::wstring wstrPath = path;
			std::replace(wstrPath.begin(), wstrPath.end(), L'\\', L'/');
			filePathes.push_back(wstrPath);
		}
	}

	return filePathes;
}

std::wstring Path::ToRelativePath(const std::wstring& absolutePath)
{
	return fs::relative(absolutePath, std::filesystem::current_path());
}

std::wstring Path::ToRelativePath(const std::wstring& absolutePath, const std::wstring& base)
{
	return fs::relative(absolutePath, base);
}

std::wstring Path::ToAbsolutePath(const std::wstring& relativePath)
{
	return fs::absolute(relativePath);
}