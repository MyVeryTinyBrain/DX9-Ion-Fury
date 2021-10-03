#include "EngineBase.h"
#include "RightTriangleUserMesh.h"

RightTriangleUserMesh::RightTriangleUserMesh() : UserMesh()
{
}

RightTriangleUserMesh::RightTriangleUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

RightTriangleUserMesh::~RightTriangleUserMesh()
{
}

void RightTriangleUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	//         1 |         4       
	//           | 
	//           | 
	// 0       2 | 3       5
	// back      | forward
	//
	// 4       1 | 1       4 | 9       7 | 10      12
	//           | 			 |           | 
	//           | 			 |           | 
	// 3       0 | 2       5 | 8       6 | 11      13
	// left      | right	 | left      | right
	//						  
	// 0       2 |			 | 14     15 |
	//           |			 |           |
	//           |			 |           |
	// 3       5 |			 | 16     17 |
	// bottom    |			 | bottom    |

	numVertices = 18;
	numIncides = 8;
}

void RightTriangleUserMesh::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	// back
	vertices[0].position = Vec3(-1.0f, -1.0f, -1.0f) * 0.5f;
	vertices[1].position = Vec3(+1.0f, +1.0f, -1.0f) * 0.5f;
	vertices[2].position = Vec3(+1.0f, -1.0f, -1.0f) * 0.5f;
	vertices[0].normal = vertices[0].position.normalized();
	vertices[1].normal = vertices[1].position.normalized();
	vertices[2].normal = vertices[2].position.normalized();
	vertices[0].uv = Vec2(0, 1);
	vertices[1].uv = Vec2(1, 0);
	vertices[2].uv = Vec2(1, 1);

	// forward
	vertices[3].position = Vec3(-1.0f, -1.0f, +1.0f) * 0.5f;
	vertices[4].position = Vec3(+1.0f, +1.0f, +1.0f) * 0.5f;
	vertices[5].position = Vec3(+1.0f, -1.0f, +1.0f) * 0.5f;
	vertices[3].normal = vertices[3].position.normalized();
	vertices[4].normal = vertices[4].position.normalized();
	vertices[5].normal = vertices[5].position.normalized();
	vertices[3].uv = Vec2(1, 1);
	vertices[4].uv = Vec2(0, 0);
	vertices[5].uv = Vec2(0, 1);

	// left
	vertices[6].position = vertices[0].position;
	vertices[7].position = vertices[1].position;
	vertices[8].position = vertices[3].position;
	vertices[9].position = vertices[4].position;
	vertices[6].normal = vertices[6].position.normalized();
	vertices[7].normal = vertices[7].position.normalized();
	vertices[8].normal = vertices[8].position.normalized();
	vertices[9].normal = vertices[9].position.normalized();
	vertices[6].uv = Vec2(0, 0);
	vertices[7].uv = Vec2(1, 0);
	vertices[8].uv = Vec2(0, 1);
	vertices[9].uv = Vec2(1, 1);

	// right
	vertices[10].position = vertices[1].position;
	vertices[11].position = vertices[2].position;
	vertices[12].position = vertices[4].position;
	vertices[13].position = vertices[5].position;
	vertices[10].normal = vertices[10].position.normalized();
	vertices[11].normal = vertices[11].position.normalized();
	vertices[12].normal = vertices[12].position.normalized();
	vertices[13].normal = vertices[13].position.normalized();
	vertices[10].uv = Vec2(0, 0);
	vertices[11].uv = Vec2(1, 0);
	vertices[12].uv = Vec2(0, 1);
	vertices[13].uv = Vec2(1, 1);

	// bottom
	vertices[14].position = vertices[0].position;
	vertices[15].position = vertices[2].position;
	vertices[16].position = vertices[3].position;
	vertices[17].position = vertices[5].position;
	vertices[14].normal = vertices[14].position.normalized();
	vertices[15].normal = vertices[15].position.normalized();
	vertices[16].normal = vertices[16].position.normalized();
	vertices[17].normal = vertices[17].position.normalized();
	vertices[14].uv = Vec2(0, 0);
	vertices[15].uv = Vec2(1, 0);
	vertices[16].uv = Vec2(0, 1);
	vertices[17].uv = Vec2(1, 1);

	UnlockVertexBuffer();
}

void RightTriangleUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	// back
	indices[0] = Index(0, 1, 2);

	// forward
	indices[1] = Index(3, 5, 4);

	// left
	indices[2] = Index(8, 7, 6);
	indices[3] = Index(8, 9, 7);

	// right
	indices[4] = Index(11, 12, 13);
	indices[5] = Index(11, 10, 12);

	// bottom
	indices[6] = Index(16, 15, 17);
	indices[7] = Index(16, 14, 15);

	UnlockIndexBuffer();
}

IClonable* RightTriangleUserMesh::Clone()
{
	RightTriangleUserMesh* clone = new RightTriangleUserMesh;

	clone->CopyFrom(this);

	return clone;
}
