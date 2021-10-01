#include "EngineBase.h"
#include "ResourceManager.h"
#include "Resource.h"

ResourceObject* Resource::Find(const wstring& localPath)
{
	return ResourceManager::GetInstance()->Find(localPath);
}

bool Resource::Exist(const wstring& localPath)
{
	return ResourceManager::GetInstance()->Exist(localPath);
}
