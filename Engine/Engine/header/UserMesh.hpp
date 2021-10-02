#pragma once
#include "UserMesh.h"
#include "ResourceManager.h"

template<class T>
inline T* UserMesh::Create(const wstring& localPath, bool isShared)
{
	if (ResourceManager::GetInstance()->Exist(localPath))
	{
		return nullptr;
	}

	T* instance = new T(localPath, isShared);

	UserMesh* userMesh = static_cast<UserMesh*>(instance);
	InitializeUserMesh(userMesh);
	ResourceManager::GetInstance()->AddResource(userMesh);

	return instance;
}

template<class T>
inline T* UserMesh::CreateUnmanaged()
{
	T* instance = new T();

	UserMesh* userMesh = static_cast<UserMesh*>(instance);
	InitializeUserMesh(userMesh);
	return instance;
}
