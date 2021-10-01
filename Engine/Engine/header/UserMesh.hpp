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

	userMesh->InitializeNums(userMesh->m_numVertices, userMesh->m_numIndices);
	userMesh->CreateVertexBuffer(userMesh->m_numVertices);
	userMesh->CreateIndexBuffer(userMesh->m_numIndices);
	userMesh->CreateStoredVertexBuffer(userMesh->m_numVertices);
	userMesh->CreateStoredIndexBuffer(userMesh->m_numIndices);

	userMesh->InitializeVertices();

	userMesh->InitializeIndices();

	userMesh->ResetStoredVertexBuffer();
	userMesh->ResetStoredIndexBuffer();

	ResourceManager::GetInstance()->AddResource(userMesh);

	return instance;
}

template<class T>
inline T* UserMesh::CreateUnmanaged()
{
	T* instance = new T();

	UserMesh* userMesh = static_cast<UserMesh*>(instance);

	userMesh->InitializeNums(userMesh->m_numVertices, userMesh->m_numIndices);
	userMesh->CreateVertexBuffer(userMesh->m_numVertices);
	userMesh->CreateIndexBuffer(userMesh->m_numIndices);
	userMesh->CreateStoredVertexBuffer(userMesh->m_numVertices);
	userMesh->CreateStoredIndexBuffer(userMesh->m_numIndices);

	userMesh->InitializeVertices();

	userMesh->InitializeIndices();

	userMesh->ResetStoredVertexBuffer();
	userMesh->ResetStoredIndexBuffer();

	return instance;
}
