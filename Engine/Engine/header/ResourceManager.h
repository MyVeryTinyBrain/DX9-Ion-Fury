#pragma once

class ResourceObject;

class ResourceManager
{
private:

	DeclareSingletone(ResourceManager);

	ResourceManager() = default;

	~ResourceManager();

public:

	void ReleaseAllResources();

	void ReleaseSharedResources();

	void ReleaseUnsharedResources();

	void ReleaseResource(ResourceObject* resource);

	ResourceObject* Find(const wstring& localPath) const;

	template <class T>
	T* FindAs(const wstring& localPath) const;

	bool Exist(const wstring& localPath) const;

	bool AddResource(ResourceObject* resource);

private:

	// wstring: local path
	// ResourceObject*: resource
	using Resources = std::unordered_map<wstring, ResourceObject*>;

	Resources m_resources;
};

#include "ResourceManager.hpp"

