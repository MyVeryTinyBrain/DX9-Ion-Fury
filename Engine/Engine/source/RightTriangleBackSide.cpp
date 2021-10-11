#include "EngineBase.h"
#include "RightTriangleBackSide.h"

RightTriangleBackSide::RightTriangleBackSide() : UserMesh()
{
}

RightTriangleBackSide::RightTriangleBackSide(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

RightTriangleBackSide::~RightTriangleBackSide()
{
}

void RightTriangleBackSide::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 3;
	numIncides = 1;
}

void RightTriangleBackSide::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	// back
	vertices[0].position = Vec3(-1.0f, -1.0f, -1.0f) * 0.5f;
	vertices[1].position = Vec3(+1.0f, +1.0f, -1.0f) * 0.5f;
	vertices[2].position = Vec3(+1.0f, -1.0f, -1.0f) * 0.5f;
	vertices[0].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[1].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[2].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[0].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
	vertices[1].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
	vertices[2].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

	UnlockVertexBuffer();
}

void RightTriangleBackSide::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	// back
	indices[0] = Index(0, 1, 2);

	UnlockIndexBuffer();
}

IClonable* RightTriangleBackSide::Clone()
{
	RightTriangleBackSide* clone = new RightTriangleBackSide;

	clone->CopyFrom(this);

	return clone;
}