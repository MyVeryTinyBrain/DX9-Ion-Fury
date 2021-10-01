#include "EngineBase.h"
#include "SphereUserMesh.h"

#define BOTTOM_VERTEX_INDEX		(m_step * m_step + 1)
#define TOP_VERTEX_INDEX		(m_step * m_step + 0)

SphereUserMesh::SphereUserMesh() : UserMesh()
{
}

SphereUserMesh::SphereUserMesh(const wstring& localPath, bool isShared) : UserMesh(localPath, isShared)
{
}

SphereUserMesh::~SphereUserMesh()
{
}

void SphereUserMesh::InitializeNums(unsigned int& numVertices, unsigned int& numIncides)
{
	// 각 층을 구성하는 step개의 정점을 step개
	// 위 아래의 꼭지점 두 개
	numVertices = (m_step * m_step) + (2);

	// 각 층마다 step개의 사각형 층을 step개
	numIncides = 2 * m_step * m_step;
}

void SphereUserMesh::InitializeVertices()
{
	Vertex* vertices = LockVertexBuffer();

	vertices[TOP_VERTEX_INDEX].position = Vec2::up() * 0.5f;
	vertices[TOP_VERTEX_INDEX].normal = Vec2::up();
	vertices[TOP_VERTEX_INDEX].uv = Vec2(0, 0);
	vertices[BOTTOM_VERTEX_INDEX].position = Vec2::down() * 0.5f;
	vertices[BOTTOM_VERTEX_INDEX].normal = Vec2::down();
	vertices[BOTTOM_VERTEX_INDEX].uv = Vec2(0, 1);

	constexpr float p = 8.0f;
	for (DWORD i = 0; i < m_step; ++i)
	{
		float yPercent = float(i + 1) / float(m_step + 1);
		if (yPercent < 0.5f)yPercent = 2.0f * yPercent * yPercent;
		else yPercent = -2.0f * powf(yPercent - 1, 2) + 1;
		float y = 0.5f - yPercent;
		Vec3 yPos = Vec3(0, y, 0);
		float dist = sqrtf(1 - powf(2 * y, 2)) * 0.5f;

		for (DWORD j = 0; j < m_step; ++j)
		{
			float anglePercent = float(j) / float(m_step - 1);
			float angle = anglePercent * 360.0f;
			float radian = angle * Deg2Rad;
			Vec3 direction = Vec3(cosf(radian), 0, sinf(radian)) * dist;

			DWORD idx = i * m_step + j;
			vertices[idx].position = direction + yPos;
			vertices[idx].normal = vertices[idx].position.normalized();
			vertices[idx].uv.x = float(j) / float(m_step - 1);
			vertices[idx].uv.y = yPercent;
		}
	}

	UnlockVertexBuffer();
}

void SphereUserMesh::InitializeIndices()
{
	Index* indices = LockIndexBuffer();

	DWORD idx = 0;
	for (DWORD i = 0; i < m_step; ++i)
	{
		DWORD yIdx = i * m_step;
		DWORD yUpIdx = (i - 1) * m_step;
		DWORD yDownIdx = (i + 1) * m_step;
		DWORD yTopIdx = (i * 0) * m_step;
		DWORD yBottomIdx = (i * (m_step - 1)) * m_step;

		BOOL isTop = (i == 0);
		BOOL isBottom = (i + 1 == m_step);

		for (DWORD j = 0; j < m_step; ++j)
		{
			DWORD xIdx = j;
			DWORD xBackIdx = j - 1;
			DWORD xNextIdx = j + 1;
			DWORD xLeftIdx = 0;
			DWORD xRightIdx = m_step - 1;

			BOOL isLeft = (j == 0);
			BOOL isRight = (j + 1 == m_step);

			DWORD t0, t1, t2;
			DWORD b0, b1, b2;

			t0 = yIdx + xIdx;
			t1 = yIdx + xNextIdx;
			if (isRight) t1 = yIdx + xLeftIdx;
			t2 = yDownIdx + xIdx;
			if (isBottom) t2 = BOTTOM_VERTEX_INDEX;

			indices[idx++] = Index(t0, t1, t2);

			b0 = yIdx + xIdx;
			b1 = yIdx + xBackIdx;
			if (isLeft) b1 = yIdx + xRightIdx;
			b2 = yUpIdx + xIdx;
			if (isTop) b2 = TOP_VERTEX_INDEX;

			indices[idx++] = Index(b0, b1, b2);
		}
	}

	UnlockIndexBuffer();
}

IClonable* SphereUserMesh::Clone()
{
	SphereUserMesh* clone = new SphereUserMesh;

	clone->CopyFrom(this);

	return clone;
}
