#include "EngineBase.h"
#include "QuadUserMesh.h"

QuadUserMesh::QuadUserMesh() : UserMesh()
{
}

QuadUserMesh::QuadUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

QuadUserMesh::~QuadUserMesh()
{
}

void QuadUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 4;
	numIncides = 2;
}

void QuadUserMesh::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	// 0 1
	// 3 2

	vertices[0].position = Vec3(-0.5f, +0.5f, 0.0f);
	vertices[1].position = Vec3(+0.5f, +0.5f, 0.0f);
	vertices[2].position = Vec3(+0.5f, -0.5f, 0.0f);
	vertices[3].position = Vec3(-0.5f, -0.5f, 0.0f);

	vertices[0].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[1].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[2].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[3].normal = Vec3(0.0f, 0.0f, -1.0f);

	vertices[0].uv = Vec2(0.0f, 0.0f);
	vertices[1].uv = Vec2(1.0f, 0.0f);
	vertices[2].uv = Vec2(1.0f, 1.0f);
	vertices[3].uv = Vec2(0.0f, 1.0f);

	UnlockVertexBuffer();
}

void QuadUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	indices[0] = Index(0, 1, 2);
	indices[1] = Index(0, 2, 3);

	UnlockIndexBuffer();
}

IClonable* QuadUserMesh::Clone()
{
	QuadUserMesh* clone = new QuadUserMesh;

	clone->CopyFrom(this);

	return clone;
}
