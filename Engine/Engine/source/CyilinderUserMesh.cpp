#include "EngineBase.h"
#include "CyilinderUserMesh.h"

#define CYLINDER_ROUND			(0)
#define CYLINDER_ROUND_TOP		(CYLINDER_ROUND)
#define CYLINDER_ROUND_BOTTOM	(CYLINDER_ROUND_TOP + m_slice)
#define CAP_TOP					(CYLINDER_ROUND_BOTTOM + m_slice)
#define CAP_BOTTOM				(CAP_TOP + m_slice)
#define CAP_TOP_CENTER			(CAP_BOTTOM + m_slice)
#define CAP_BOTTOM_CENTER		(CAP_TOP_CENTER + 1)

CyilinderUserMesh::CyilinderUserMesh() : UserMesh()
{
}

CyilinderUserMesh::CyilinderUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

CyilinderUserMesh::~CyilinderUserMesh()
{
}

void CyilinderUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	// 실린더를 두르는 위 아래 원을 구성하는 slice개의 정점 세트 두 개
	// 실린더를 덮는 위 아래 원을 구성하는 slice개의 정점 세트 두 개
	// 실린더를 덮는 위 아래 원의 중심점 정점 두 개
	numVertices = (m_slice * 2) + (m_slice * 2) + (2);

	// 실런더를 두르는 메쉬 구성을 위한 slice개의 사각형 구성을 위한 slice * 2개의 삼각형 세트
	// 실린더의 덮개 메쉬 구성을 위한 slice개의 삼각형 구성을 위한 slice개의 삼각형 세트 두 개
	numIncides = (m_slice * 2) + m_slice * 2;
}

void CyilinderUserMesh::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	vertices[CAP_TOP_CENTER].position = Vec2::up() * m_halfHeight;
	vertices[CAP_TOP_CENTER].normal = Vec2::up();
	vertices[CAP_TOP_CENTER].uv = Vec2(0.5f * uvScale.x, 0.5f * uvScale.y);
	vertices[CAP_BOTTOM_CENTER].position = Vec2::down() * m_halfHeight;
	vertices[CAP_BOTTOM_CENTER].normal = Vec2::down();
	vertices[CAP_BOTTOM_CENTER].uv = Vec2(0.5f * uvScale.x, 0.5f * uvScale.y);

	for (DWORD i = 0; i <= 1; ++i)
	{
		float yPercent = float(i);
		float y = (0.5f - yPercent) * 2.0f;
		Vec3 yPos = Vec3(0, y, 0) * m_halfHeight;

		for (DWORD j = 0; j < m_slice; ++j)
		{
			float anglePercent = float(j) / float(m_slice - 1);
			float angle = anglePercent * 360.0f;
			float radian = angle * Deg2Rad;
			Vec3 direction = Vec3(cosf(radian), 0, sinf(radian)) * m_radius;

			DWORD idx = i * m_slice + j;
			vertices[idx].position = direction + yPos;
			vertices[idx].normal = direction.normalized();
			vertices[idx].uv.x = float(j) / float(m_slice - 1) * uvScale.x;
			vertices[idx].uv.y = yPercent * uvScale.y;

			DWORD capIdx;
			if (i == 0) capIdx = CAP_TOP + j;
			else capIdx = CAP_BOTTOM + j;
			vertices[capIdx].position = direction + yPos;
			vertices[capIdx].normal = (i == 0 ? Vec3::up() : Vec3::down());
			vertices[capIdx].uv.x = (vertices[capIdx].position.x + 0.5f) * uvScale.x;
			vertices[capIdx].uv.y = (vertices[capIdx].position.z + 0.5f) * uvScale.y;
		}
	}

	UnlockVertexBuffer();
}

void CyilinderUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	DWORD idx = 0;

	for (DWORD i = 0; i < m_slice; ++i)
	{
		DWORD i0, i1, i2;	// 몸통 두르기 위쪽에서 아래쪽 삼각형
		DWORD j0, j1, j2;	// 몸통 두르기 아래쪽에서 위쪽 삼각형
		DWORD k0, k1, k2;	// 위쪽 캡
		DWORD l0, l1, l2;	// 아래쪽 캡

		i0 = CYLINDER_ROUND_TOP + i;
		i1 = CYLINDER_ROUND_TOP + i + 1;
		if (i + 1 == m_slice) i1 = CYLINDER_ROUND_TOP;
		i2 = CYLINDER_ROUND_BOTTOM + i;

		j0 = CYLINDER_ROUND_BOTTOM + i;
		j1 = CYLINDER_ROUND_TOP + i + 1;
		if (i + 1 == m_slice) j1 = CYLINDER_ROUND_TOP;
		j2 = CYLINDER_ROUND_BOTTOM + i + 1;
		if (i + 1 == m_slice) j2 = CYLINDER_ROUND_BOTTOM;

		k0 = CAP_TOP + i;
		k1 = CAP_TOP + i + 1;
		if (i + 1 == m_slice) k1 = CAP_TOP;
		k2 = CAP_TOP_CENTER;

		l0 = CAP_BOTTOM + i;
		l1 = CAP_BOTTOM + i + 1;
		if (i + 1 == m_slice) l1 = CAP_BOTTOM;
		l2 = CAP_BOTTOM_CENTER;

		indices[idx++] = Index(i0, i1, i2);
		indices[idx++] = Index(j0, j1, j2);
		indices[idx++] = Index(k2, k1, k0);
		indices[idx++] = Index(l0, l1, l2);
	}

	UnlockIndexBuffer();
}

IClonable* CyilinderUserMesh::Clone()
{
	CyilinderUserMesh* clone = new CyilinderUserMesh;

	clone->CopyFrom(this);

	return clone;
}

float CyilinderUserMesh::GetHalfHeight() const
{
	return m_halfHeight;
}

void CyilinderUserMesh::SetHalfHeight(float value)
{
	if (Abs(value - m_halfHeight) <= FLT_EPSILON)
	{
		return;
	}

	m_halfHeight = value;

	InitializeVertices();
	ResetStoredVertexBuffer();
}

float CyilinderUserMesh::GetRadius() const
{
	return m_radius;
}

void CyilinderUserMesh::SetRaidus(float value)
{
	if (Abs(value - m_radius) > FLT_EPSILON)
	{
		m_radius = value;

		InitializeVertices();
		ResetStoredVertexBuffer();
	}
}
