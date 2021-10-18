#include "EngineBase.h"
#include "QuadForwardUserMesh.h"

QuadForwardUserMesh::QuadForwardUserMesh() : UserMesh()
{
}

QuadForwardUserMesh::QuadForwardUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

QuadForwardUserMesh::~QuadForwardUserMesh()
{
}

void QuadForwardUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 4;
	numIncides = 2;
}

void QuadForwardUserMesh::InitializeVertices()
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

	vertices[0].uv = Vec2(0.0f * uvScale.x, 0.0f * uvScale.y);
	vertices[1].uv = Vec2(1.0f * uvScale.x, 0.0f * uvScale.y);
	vertices[2].uv = Vec2(1.0f * uvScale.x, 1.0f * uvScale.y);
	vertices[3].uv = Vec2(0.0f * uvScale.x, 1.0f * uvScale.y);

	UnlockVertexBuffer();
}

void QuadForwardUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	indices[0] = Index(0, 1, 2);
	indices[1] = Index(0, 2, 3);

	UnlockIndexBuffer();
}

IClonable* QuadForwardUserMesh::Clone()
{
	QuadForwardUserMesh* clone = new QuadForwardUserMesh;

	clone->CopyFrom(this);

	return clone;
}
