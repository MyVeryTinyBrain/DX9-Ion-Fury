#include "EngineBase.h"
#include "QuadRightUserMesh.h"

QuadRightUserMesh::QuadRightUserMesh() : UserMesh()
{
}

QuadRightUserMesh::QuadRightUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

QuadRightUserMesh::~QuadRightUserMesh()
{
}

void QuadRightUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 4;
	numIncides = 2;
}

void QuadRightUserMesh::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	// 0 1
	// 3 2

	vertices[0].position = Vec3(0.0f, +0.5f, -0.5f);
	vertices[1].position = Vec3(0.0f, +0.5f, +0.5f);
	vertices[2].position = Vec3(0.0f, -0.5f, +0.5f);
	vertices[3].position = Vec3(0.0f, -0.5f, -0.5f);

	vertices[0].normal = Vec3(+1.0f, 0.0f, 0.0f);
	vertices[1].normal = Vec3(+1.0f, 0.0f, 0.0f);
	vertices[2].normal = Vec3(+1.0f, 0.0f, 0.0f);
	vertices[3].normal = Vec3(+1.0f, 0.0f, 0.0f);

	vertices[0].uv = Vec2(0.0f * uvScale.x, 0.0f * uvScale.y);
	vertices[1].uv = Vec2(1.0f * uvScale.x, 0.0f * uvScale.y);
	vertices[2].uv = Vec2(1.0f * uvScale.x, 1.0f * uvScale.y);
	vertices[3].uv = Vec2(0.0f * uvScale.x, 1.0f * uvScale.y);

	UnlockVertexBuffer();
}

void QuadRightUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	indices[0] = Index(0, 1, 2);
	indices[1] = Index(0, 2, 3);

	UnlockIndexBuffer();
}

IClonable* QuadRightUserMesh::Clone()
{
	QuadRightUserMesh* clone = new QuadRightUserMesh;

	clone->CopyFrom(this);

	return clone;
}
