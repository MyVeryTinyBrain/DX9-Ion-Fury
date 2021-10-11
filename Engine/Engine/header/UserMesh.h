#pragma once

#include "ResourceObject.h"

class UserMesh abstract : public ResourceObject, public IClonable
{
	friend class ResourceManager;

protected:

	// Constructor for unmanaged resource
	UserMesh();

	// Construct for managed resource
	UserMesh(const wstring& localPath, bool isShared);

	virtual ~UserMesh();

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) = 0;

	virtual void InitializeVertices() = 0;

	virtual void InitializeIndices() = 0;

public:

	template <class T>
	static T* Create(const wstring& localPath, bool isShared);

	template <class T>
	static T* CreateUnmanaged();

	// Return to unmanaged
	virtual IClonable* Clone() = 0;

public:

	void Draw();

	unsigned int GetNumVertices() const;

	unsigned int GetNumFaces() const;

	Vertex* GetStoredVertexBuffer() const;

	Index* GetStoredIndexBuffer() const;

	Vertex* LockVertexBuffer();

	Index* LockIndexBuffer();

	void UnlockVertexBuffer();

	void UnlockIndexBuffer();

	void ResetStoredVertexBuffer();

	void ResetStoredIndexBuffer();

	bool Raycast(Vec3& hitPoint, const Vec3& worldRayPoint, const Vec3& worldRayDir, const Mat4& meshLocalToWorld);

	const Vec2& GetUVScale() const;

	void SetUVScale(const Vec2& uvScale);

	__declspec(property (get = GetNumVertices)) unsigned int numVertices;

	__declspec(property (get = GetNumIndices)) unsigned int numIndices;

	__declspec(property (get = GetNumFaces)) unsigned int numFaces;

	__declspec(property (get = GetUVScale, put = SetUVScale)) const Vec2& uvScale;

protected:

	void CreateVertexBuffer(unsigned int numVertices);

	void CreateIndexBuffer(unsigned int numIndices);

	void CreateStoredVertexBuffer(unsigned int numVertices);

	void CreateStoredIndexBuffer(unsigned int numIndices);

	void CopyFrom(UserMesh* other);

private:

	static void InitializeUserMesh(UserMesh* userMesh);

	static void ReleaseUnmanagedUserMesh(UserMesh* userMesh);

private:

	unsigned int m_numVertices = 0;

	unsigned int m_numIndices = 0;

	IDirect3DVertexBuffer9* m_vertices = nullptr;

	IDirect3DIndexBuffer9* m_indices = nullptr;

	Vertex* m_storedVertexBuffer = nullptr;

	Index* m_storedIndexBuffer = nullptr;

	Vec2 m_uvScale = Vec2(1, 1);
};

#include "UserMesh.hpp"
