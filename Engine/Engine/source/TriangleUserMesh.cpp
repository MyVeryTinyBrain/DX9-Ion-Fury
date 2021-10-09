#include "EngineBase.h"
#include "TriangleUserMesh.h"

TriangleUserMesh::TriangleUserMesh() : UserMesh()
{
}

TriangleUserMesh::TriangleUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

TriangleUserMesh::~TriangleUserMesh()
{
}

void TriangleUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	numVertices = 18;
	numIncides = 8;
}

void TriangleUserMesh::InitializeVertices()
{
	//     1     |     4       
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

	Vertex* vertices = LockVertexBuffer();

	// back
	vertices[0].position = Vec3(-1.0f, -1.0f, -1.0f) * 0.5f;
	vertices[1].position = Vec3(+0.0f, +1.0f, -1.0f) * 0.5f;
	vertices[2].position = Vec3(+1.0f, -1.0f, -1.0f) * 0.5f;
	vertices[0].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[1].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[2].normal = Vec3(0.0f, 0.0f, -1.0f);
	vertices[0].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
	vertices[1].uv = Vec2(0.5f * uvScale.x, 0 * uvScale.y);
	vertices[2].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

	// forward
	vertices[3].position = Vec3(-1.0f, -1.0f, +1.0f) * 0.5f;
	vertices[4].position = Vec3(+0.0f, +1.0f, +1.0f) * 0.5f;
	vertices[5].position = Vec3(+1.0f, -1.0f, +1.0f) * 0.5f;
	vertices[3].normal = Vec3(0.0f, 0.0f, +1.0f);
	vertices[4].normal = Vec3(0.0f, 0.0f, +1.0f);
	vertices[5].normal = Vec3(0.0f, 0.0f, +1.0f);
	vertices[3].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);
	vertices[4].uv = Vec2(0.5f * uvScale.x, 0 * uvScale.y);
	vertices[5].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);

	// left
	vertices[6].position = vertices[0].position;
	vertices[7].position = vertices[1].position;
	vertices[8].position = vertices[3].position;
	vertices[9].position = vertices[4].position;
	vertices[6].normal = Quat::FromEuler(0, 0, 45) * Vec3::up();
	vertices[7].normal = Quat::FromEuler(0, 0, 45) * Vec3::up();
	vertices[8].normal = Quat::FromEuler(0, 0, 45) * Vec3::up();
	vertices[9].normal = Quat::FromEuler(0, 0, 45) * Vec3::up();
	vertices[6].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
	vertices[7].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
	vertices[8].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
	vertices[9].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

	// right
	vertices[10].position = vertices[1].position;
	vertices[11].position = vertices[2].position;
	vertices[12].position = vertices[4].position;
	vertices[13].position = vertices[5].position;
	vertices[10].normal = Quat::FromEuler(0, 0, -45) * Vec3::up();
	vertices[11].normal = Quat::FromEuler(0, 0, -45) * Vec3::up();
	vertices[12].normal = Quat::FromEuler(0, 0, -45) * Vec3::up();
	vertices[13].normal = Quat::FromEuler(0, 0, -45) * Vec3::up();
	vertices[10].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
	vertices[11].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
	vertices[12].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
	vertices[13].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

	// bottom
	vertices[14].position = vertices[0].position;
	vertices[15].position = vertices[2].position;
	vertices[16].position = vertices[3].position;
	vertices[17].position = vertices[5].position;
	vertices[14].normal = Vec3(0.0f, -1.0f, 0.0f);
	vertices[15].normal = Vec3(0.0f, -1.0f, 0.0f);
	vertices[16].normal = Vec3(0.0f, -1.0f, 0.0f);
	vertices[17].normal = Vec3(0.0f, -1.0f, 0.0f);
	vertices[14].uv = Vec2(0 * uvScale.x, 0 * uvScale.y);
	vertices[15].uv = Vec2(1 * uvScale.x, 0 * uvScale.y);
	vertices[16].uv = Vec2(0 * uvScale.x, 1 * uvScale.y);
	vertices[17].uv = Vec2(1 * uvScale.x, 1 * uvScale.y);

	UnlockVertexBuffer();
}

void TriangleUserMesh::InitializeIndices()
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

IClonable* TriangleUserMesh::Clone()
{
	TriangleUserMesh* clone = new TriangleUserMesh;

	clone->CopyFrom(this);

	return clone;
}
