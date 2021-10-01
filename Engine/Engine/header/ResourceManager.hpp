#pragma once

#include "ResourceManager.h"

template<class T>
inline T* ResourceManager::FindAs(const wstring& localPath) const
{
	ResourceObject* resource = Find(localPath);

	if (!resource)
		return nullptr;

	T* cast = dynamic_cast<T*>(resource);

	if (!cast)
		return nullptr;

	return cast;
}