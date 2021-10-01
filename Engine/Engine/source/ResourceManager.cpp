#include "EngineBase.h"
#include "ResourceManager.h"
#include "ResourceObject.h"

ImplementSingletone(ResourceManager);

ResourceManager::~ResourceManager()
{
	ReleaseAllResources();
}

void ResourceManager::ReleaseAllResources()
{
	for (auto& pair : m_resources)
	{
		SafeDeleteInline(pair.second);
	}
	m_resources.clear();
}

void ResourceManager::ReleaseSharedResources()
{
	for (auto it = m_resources.begin(); it != m_resources.end();)
	{
		ResourceObject* resource = it->second;

		if (!resource->isShared)
		{
			++it;
			continue;
		}

		SafeDeleteInline(resource);
		it = m_resources.erase(it);
	}
}

void ResourceManager::ReleaseUnsharedResources()
{
	for (auto it = m_resources.begin(); it != m_resources.end();)
	{
		ResourceObject* resource = it->second;

		if (resource->isShared)
		{
			++it;
			continue;
		}

		SafeDeleteInline(resource);
		it = m_resources.erase(it);
	}
}

void ResourceManager::ReleaseResource(ResourceObject* resource)
{
	wstring localPath = resource->localPath;

	SafeDeleteInline(resource);

	auto find_it = m_resources.find(localPath);

	if (find_it == m_resources.end())
		return;

	m_resources.erase(find_it);
}

ResourceObject* ResourceManager::Find(const wstring& localPath) const
{
	auto find_it = m_resources.find(localPath);

	if (find_it == m_resources.end())
		return nullptr;

	return find_it->second;
}

bool ResourceManager::Exist(const wstring& localPath) const
{
	return Find(localPath);
}

bool ResourceManager::AddResource(ResourceObject* resource)
{
	auto insert_result = m_resources.emplace(resource->localPath, resource);
	return insert_result.second;
}
