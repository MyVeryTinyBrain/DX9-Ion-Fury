#pragma once
#include "Resource.h"
#include "ResourceManager.h"

template<class T>
T* Resource::FindAs(const wstring& localPath)
{
	return ResourceManager::GetInstance()->FindAs<T>(localPath);
}