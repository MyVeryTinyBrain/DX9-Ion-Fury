#include "EngineBase.h"
#include "RightTriangleFrontSide.h"

RightTriangleFrontSide::RightTriangleFrontSide() : UserMesh()
{
}

RightTriangleFrontSide::RightTriangleFrontSide(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

RightTriangleFrontSide::~RightTriangleFrontSide()
{
}

void RightTriangleFrontSide::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 3;
	numIncides = 1;
}

void RightTriangleFrontSide::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	// forward
	vertices[0].position = Vec3(-1.0f, -1.0f, +1.0f) * 0.5f;
	vertices[1].position = Vec3(+1.0f, +1.0f, +1.0f) * 0.5f;
	vertices[2].position = Vec3(+1.0f, -1.0f, +1.0f) * 0.5f;
	vertices[0].normal = Vec3(0.0f, 0.0f, +1.0f);
	vertices[1].normal = Vec3(0.0f, 0.0f, +1.0f);
	vertices[2].normal = Vec3(0.0f, 0.0f, +1.0f);
	vertices[0].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);
	vertices[1].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
	vertices[2].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);

	UnlockVertexBuffer();
}

void RightTriangleFrontSide::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	// forward
	indices[0] = Index(0, 2, 1);

	UnlockIndexBuffer();
}

IClonable* RightTriangleFrontSide::Clone()
{
	RightTriangleFrontSide* clone = new RightTriangleFrontSide;

	clone->CopyFrom(this);

	return clone;
}