#pragma once

namespace Path
{
	struct QueryFilePathCallback
	{
		virtual bool Allow(const std::wstring& path) = 0;
	};

	std::vector<std::wstring> QueryFilePath(const std::wstring& directory);

	std::vector<std::wstring> QueryFilePath(const std::wstring& directory, const std::wstring& extension);

	std::vector<std::wstring> QueryFilePath(const std::wstring& directory, Path::QueryFilePathCallback* callback);

	std::wstring ToRelativePath(const std::wstring& absolutePath);

	std::wstring ToRelativePath(const std::wstring& absolutePath, const std::wstring& base);

	std::wstring ToAbsolutePath(const std::wstring& relativePath);
};

