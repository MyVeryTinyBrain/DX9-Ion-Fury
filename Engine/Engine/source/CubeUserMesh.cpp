#include "EngineBase.h"
#include "CubeUserMesh.h"
#include "..\header\CubeUserMesh.h"

CubeUserMesh::CubeUserMesh() : UserMesh()
{
}

CubeUserMesh::CubeUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

CubeUserMesh::~CubeUserMesh()
{
}

void CubeUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 24;
	numIncides = 12;
}

void CubeUserMesh::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	if (vertices)
	{
		// front
		// x, y
		// 1	2
		// 0	3
		vertices[0].position = Vec3(-1.0f, -1.0f, -1.0f) * 0.5f;
		vertices[1].position = Vec3(-1.0f, +1.0f, -1.0f) * 0.5f;
		vertices[2].position = Vec3(+1.0f, +1.0f, -1.0f) * 0.5f;
		vertices[3].position = Vec3(+1.0f, -1.0f, -1.0f) * 0.5f;
		vertices[0].normal = Vec3(0, 0, -1);
		vertices[1].normal = Vec3(0, 0, -1);
		vertices[2].normal = Vec3(0, 0, -1);
		vertices[3].normal = Vec3(0, 0, -1);
		vertices[0].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
		vertices[1].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
		vertices[2].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
		vertices[3].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

		// back
		// -x, y
		// 6	5
		// 7	4
		vertices[4].position = Vec3(-1.0f, -1.0f, +1.0f) * 0.5f;
		vertices[5].position = Vec3(-1.0f, +1.0f, +1.0f) * 0.5f;
		vertices[6].position = Vec3(+1.0f, +1.0f, +1.0f) * 0.5f;
		vertices[7].position = Vec3(+1.0f, -1.0f, +1.0f) * 0.5f;
		vertices[4].normal = Vec3(0, 0, +1);
		vertices[5].normal = Vec3(0, 0, +1);
		vertices[6].normal = Vec3(0, 0, +1);
		vertices[7].normal = Vec3(0, 0, +1);
		vertices[4].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);
		vertices[5].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
		vertices[6].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
		vertices[7].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);

		// left
		// -z, y
		// 11.5	9.1
		// 10.4	8.0
		vertices[8].position = vertices[0].position;
		vertices[9].position = vertices[1].position;
		vertices[10].position = vertices[4].position;
		vertices[11].position = vertices[5].position;
		vertices[8].normal = Vec3(-1, 0, 0);
		vertices[9].normal = Vec3(-1, 0, 0);
		vertices[10].normal = Vec3(-1, 0, 0);
		vertices[11].normal = Vec3(-1, 0, 0);
		vertices[8].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);
		vertices[9].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
		vertices[10].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
		vertices[11].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);

		// right
		// z, y
		// 12.2	14.6
		// 13.3	15.7
		vertices[12].position = vertices[2].position;
		vertices[13].position = vertices[3].position;
		vertices[14].position = vertices[6].position;
		vertices[15].position = vertices[7].position;
		vertices[12].normal = Vec3(+1, 0, 0);
		vertices[13].normal = Vec3(+1, 0, 0);
		vertices[14].normal = Vec3(+1, 0, 0);
		vertices[15].normal = Vec3(+1, 0, 0);
		vertices[12].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
		vertices[13].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
		vertices[14].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
		vertices[15].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

		// top
		// x, z
		// 18.5	19.6
		// 16.1	17.2
		vertices[16].position = vertices[1].position;
		vertices[17].position = vertices[2].position;
		vertices[18].position = vertices[5].position;
		vertices[19].position = vertices[6].position;
		vertices[16].normal = Vec3(0, +1, 0);
		vertices[17].normal = Vec3(0, +1, 0);
		vertices[18].normal = Vec3(0, +1, 0);
		vertices[19].normal = Vec3(0, +1, 0);
		vertices[16].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
		vertices[17].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);
		vertices[18].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
		vertices[19].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);

		// bottom
		// x, -z
		// 21.3	20.0
		// 23.7	22.4
		vertices[20].position = vertices[0].position;
		vertices[21].position = vertices[3].position;
		vertices[22].position = vertices[4].position;
		vertices[23].position = vertices[7].position;
		vertices[20].normal = Vec3(0, -1, 0);
		vertices[21].normal = Vec3(0, -1, 0);
		vertices[22].normal = Vec3(0, -1, 0);
		vertices[23].normal = Vec3(0, -1, 0);
		vertices[20].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
		vertices[21].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
		vertices[22].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);
		vertices[23].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
	}

	UnlockVertexBuffer();
}

void CubeUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	if (indices)
	{
		// front side
		indices[0] = Index(0, 1, 2);
		indices[1] = Index(0, 2, 3);

		// back side
		indices[2] = Index(4, 6, 5);
		indices[3] = Index(4, 7, 6);

		// left side
		indices[4] = Index(10, 11, 9);
		indices[5] = Index(10, 9, 8);

		// right side
		indices[6] = Index(13, 12, 14);
		indices[7] = Index(13, 14, 15);

		// top
		indices[8] = Index(16, 18, 19);
		indices[9] = Index(16, 19, 17);

		// bottom
		indices[10] = Index(22, 20, 21);
		indices[11] = Index(22, 21, 23);
	}

	UnlockIndexBuffer();
}

IClonable* CubeUserMesh::Clone()
{
	CubeUserMesh* clone = new CubeUserMesh;

	clone->CopyFrom(this);

	return clone;
}
