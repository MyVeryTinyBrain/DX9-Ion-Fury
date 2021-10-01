#pragma once

namespace Resource
{
	class ResourceObject* Find(const wstring& localPath);

	template <class T>
	T* FindAs(const wstring& localPath);

	bool Exist(const wstring& localPath);
};

#include "Resource.hpp"

