#include "EngineBase.h"
#include "UserMesh.h"
#include "GraphicDevice.h"
#include "Transform.h"

UserMesh::UserMesh() : ResourceObject()
{
}

UserMesh::UserMesh(const wstring& localPath, bool isShared) : ResourceObject(localPath, isShared)
{
}

UserMesh::~UserMesh()
{
	if (m_vertices)
	{
		m_vertices->Release();
		m_vertices = nullptr;
	}

	if (m_indices)
	{
		m_indices->Release();
		m_indices = nullptr;
	}

	SafeDelete(m_storedVertexBuffer);
	SafeDelete(m_storedIndexBuffer);
}

void UserMesh::Draw()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	device->SetStreamSource(0, m_vertices, 0, sizeof(Vertex));
	device->SetIndices(m_indices);
	device->SetFVF(Vertex::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_numVertices, 0, m_numIndices);
}

unsigned int UserMesh::GetNumVertices() const
{
	return m_numVertices;
}

unsigned int UserMesh::GetNumFaces() const
{
	return m_numIndices;
}

Vertex* UserMesh::LockVertexBuffer()
{
	Vertex* vertices = nullptr;
	m_vertices->Lock(0, sizeof(Vertex) * m_numVertices, (void**)&vertices, 0);
	return vertices;
}

Index* UserMesh::LockIndexBuffer()
{
	Index* index = nullptr;
	m_indices->Lock(0, sizeof(Index) * m_numVertices, (void**)&index, 0);
	return index;
}

void UserMesh::UnlockVertexBuffer()
{
	m_vertices->Unlock();
}

void UserMesh::UnlockIndexBuffer()
{
	m_indices->Unlock();
}

void UserMesh::ResetStoredVertexBuffer()
{
	void* vertices = nullptr;
	m_vertices->Lock(0, 0, &vertices, 0);
	memcpy(m_storedVertexBuffer, vertices, sizeof(Vertex) * m_numVertices);
	m_vertices->Unlock();
}

void UserMesh::ResetStoredIndexBuffer()
{
	void* indices = nullptr;
	m_indices->Lock(0, 0, &indices, 0);
	memcpy(m_storedIndexBuffer, indices, sizeof(Index) * m_numIndices);
	m_indices->Unlock();
}

bool UserMesh::Raycast(Vec3& hitPoint, const Vec3& worldRayPoint, const Vec3& worldRayDir, const Mat4& meshLocalToWorld)
{
	Mat4 worldToLocal = meshLocalToWorld.inversed();
	Vec3 localRayPoint = worldToLocal.MultiplyPoint(worldRayPoint);
	Vec3 localRayDir = worldToLocal.MultiplyVector(worldRayDir);

	float u, v, d;
	const Vertex* vertices = m_storedVertexBuffer;
	for (unsigned int i = 0; i < m_numIndices; ++i)
	{
		const Index& index = m_storedIndexBuffer[i];
		const Vec3& p0 = vertices[index.v0].position;
		const Vec3& p1 = vertices[index.v1].position;
		const Vec3& p2 = vertices[index.v2].position;

		if (D3DXIntersectTri(&p0, &p1, &p2, &localRayPoint, &localRayDir, &u, &v, &d))
		{
			hitPoint = p0 + u * (p1 - p0) + v * (p2 - p0);
			hitPoint = meshLocalToWorld.MultiplyPoint(hitPoint);
			return true;
		}
	}

	return false;
}

void UserMesh::CreateVertexBuffer(unsigned int numVertices)
{
	if (m_vertices)
	{
		m_vertices->Release();
		m_vertices = nullptr;
	}

	auto device = GraphicDevice::GetInstance()->GetDevice();
	HRESULT res;
	res = device->CreateVertexBuffer(
		sizeof(Vertex) * m_numVertices,
		0, // dynamic 플래그가 아니라면 모두 정적 버퍼로 생성합니다.
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertices,
		nullptr
	);
}

void UserMesh::CreateIndexBuffer(unsigned int numIndices)
{
	if (m_indices)
	{
		m_indices->Release();
		m_indices = nullptr;
	}

	auto device = GraphicDevice::GetInstance()->GetDevice();
	HRESULT res;
	res = device->CreateIndexBuffer(
		sizeof(Index) * m_numIndices,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indices,
		nullptr
	);
}

void UserMesh::CreateStoredVertexBuffer(unsigned int numVertices)
{
	SafeDelete(m_storedVertexBuffer);

	m_storedVertexBuffer = new Vertex[m_numVertices];
}

void UserMesh::CreateStoredIndexBuffer(unsigned int numIndices)
{
	SafeDelete(m_storedIndexBuffer);

	m_storedIndexBuffer = new Index[numIndices];
}

void UserMesh::CopyFrom(UserMesh* other)
{
	m_numVertices = other->m_numVertices;

	m_numIndices = other->m_numIndices;

	CreateVertexBuffer(m_numVertices);
	CreateIndexBuffer(m_numIndices);
	CreateStoredVertexBuffer(m_numVertices);

	Vertex* vertices = LockVertexBuffer();
	memcpy(m_vertices, other->m_vertices, sizeof(Vertex) * m_numVertices);
	memcpy(m_storedVertexBuffer, other->m_storedVertexBuffer, sizeof(Vertex) * m_numVertices);
	UnlockVertexBuffer();

	Index* indices = LockIndexBuffer();
	memcpy(m_indices, other->m_indices, sizeof(Index) * m_numIndices);
	UnlockIndexBuffer();
}

void UserMesh::InitializeUserMesh(UserMesh* userMesh)
{
	userMesh->InitializeNums(userMesh->m_numVertices, userMesh->m_numIndices);
	userMesh->CreateVertexBuffer(userMesh->m_numVertices);
	userMesh->CreateIndexBuffer(userMesh->m_numIndices);
	userMesh->CreateStoredVertexBuffer(userMesh->m_numVertices);
	userMesh->CreateStoredIndexBuffer(userMesh->m_numIndices);

	userMesh->InitializeVertices();
	
	userMesh->InitializeIndices();

	userMesh->ResetStoredVertexBuffer();
	userMesh->ResetStoredIndexBuffer();
}

void UserMesh::ReleaseUnmanagedUserMesh(UserMesh* userMesh)
{
	userMesh->ReleaseUnmanaged();
}
