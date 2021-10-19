#include "shared_stdafx.h"
#include "TrailRenderer.h"

void TrailRenderer::Awake()
{
	Renderer::Awake();

	material = Resource::FindAs<Material>(BuiltInNolightNoCullGeometryMaterial);
	SetTexture(0, Resource::FindAs<Texture>(BuiltInGreenTexture));
}

void TrailRenderer::OnDestroy()
{
	Renderer::OnDestroy();

	if (m_vertices)
	{
		m_vertices->Release();
		m_vertices = nullptr;
	}

	if (m_indices)
	{
		m_indices->Release();
		m_indices = nullptr;
	}
}

void TrailRenderer::LateUpdate()
{
	Renderer::LateUpdate();

	if (m_worldPoints.size() < 2)
	{
		return;
	}

	if (m_beforePoints == m_worldPoints.size())
	{
		return;
	}

	ResetBuffers();
}

void TrailRenderer::Render()
{
	Renderer::Render();

	auto device = GraphicDevice::GetInstance()->GetDevice();

	if (m_worldPoints.size() < 2)
	{
		return;
	}

	if (!m_vertices)
	{
		return;
	}

	if (!m_indices)
	{
		return;
	}

	Mat4 beforeWorld;
	Mat4 identity = Mat4::Identity();
	device->GetTransform(D3DTS_WORLD, &beforeWorld);
	device->SetTransform(D3DTS_WORLD, &identity);

	device->SetStreamSource(0, m_vertices, 0, sizeof(Vertex));
	device->SetIndices(m_indices);
	device->SetFVF(Vertex::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_numVertices, 0, m_numIndices);

	device->SetTransform(D3DTS_WORLD, &beforeWorld);
}

void TrailRenderer::AddPoint(const Vec3& point)
{
	m_worldPoints.push_back(point);
}

void TrailRenderer::RemoveFirstPoint()
{
	if (m_worldPoints.size() > 0)
	{
	m_worldPoints.erase(m_worldPoints.begin());
	}
}

void TrailRenderer::RemoveLastPoint()
{
	if (m_worldPoints.size() > 0)
	{
		m_worldPoints.erase(m_worldPoints.end());
	}
}

size_t TrailRenderer::GetPointCount() const
{
	return m_worldPoints.size();
}

float TrailRenderer::GetWidth() const
{
	return m_width;
}

void TrailRenderer::SetWidth(float value)
{
	value = Clamp(value, 0, FLT_MAX);

	m_width = value;
}

void TrailRenderer::ResetBuffers()
{
	unsigned int vertexSize = (m_worldPoints.size() * 2) * 2;
	unsigned int indexSize = ((m_worldPoints.size() - 1) * 2) * 2;

	if (m_worldPoints.size() < 2)
	{
		vertexSize = 0;
		indexSize = 0;
	}

	CreateVertexBuffer(vertexSize);
	CreateIndexBuffer(indexSize);

	ResetVertexBuffer();
	ResetIndexBuffer();
}

void TrailRenderer::CreateVertexBuffer(unsigned int numVertices)
{
	if (m_vertices)
	{
		m_vertices->Release();
		m_vertices = nullptr;
	}

	if (numVertices < 3)
	{
		m_numVertices = 0;
		return;
	}

	auto device = GraphicDevice::GetInstance()->GetDevice();
	HRESULT res;
	res = device->CreateVertexBuffer(
		sizeof(Vertex) * numVertices,
		0, // dynamic 플래그가 아니라면 모두 정적 버퍼로 생성합니다.
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertices,
		nullptr
	);

	m_numVertices = numVertices;
}

void TrailRenderer::CreateIndexBuffer(unsigned int numIndices)
{
	if (m_indices)
	{
		m_indices->Release();
		m_indices = nullptr;
	}

	if (numIndices <= 0)
	{
		m_numIndices = numIndices;
		return;
	}

	auto device = GraphicDevice::GetInstance()->GetDevice();
	HRESULT res;
	res = device->CreateIndexBuffer(
		sizeof(Index) * numIndices,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indices,
		nullptr
	);

	m_numIndices = numIndices;
}

void TrailRenderer::ResetVertexBuffer()
{
	Camera* camera = Camera::GetMainCamera();

	if (!camera)
	{
		CreateVertexBuffer(0);
		return;
	}

	if (m_numVertices < 2)
	{
		return;
	}

	Vec3 forward = camera->transform->forward;

	Vertex* vertex = LockVertexBuffer();

	size_t current = 0;

	for (size_t i = 0; i < m_worldPoints.size(); ++i)
	{
		size_t curPoint = i;
		size_t nextPoint = i + 1;
		if (nextPoint >= m_worldPoints.size())
		{
			curPoint = i - 1;
			nextPoint = i;
		}
		Vec3 lineDir = (m_worldPoints[nextPoint] - m_worldPoints[curPoint]).normalized();
		Quat q = Quat::FromToRotation(Vec3::forawrd(), lineDir);
		Vec3 moveDir = q * Vec3::right();

		float percent = float(i) / float(m_worldPoints.size() - 1);
		float uvPercent = percent;
		float scalePercent = percent;

		vertex[current].position = m_worldPoints[i] + moveDir * m_width * 0.5f * scalePercent;
		vertex[current].normal = -forward;
		vertex[current].uv = Vec2(0.0f, uvPercent);
		++current;

		vertex[current].position = m_worldPoints[i] - moveDir * m_width * 0.5f * scalePercent;
		vertex[current].normal = -forward;
		vertex[current].uv = Vec2(1.0f, uvPercent);
		++current;
	}

	for (size_t i = 0; i < m_worldPoints.size(); ++i)
	{
		size_t curPoint = i;
		size_t nextPoint = i + 1;
		if (nextPoint >= m_worldPoints.size())
		{
			curPoint = i - 1;
			nextPoint = i;
		}
		Vec3 lineDir = (m_worldPoints[nextPoint] - m_worldPoints[curPoint]).normalized();
		Quat q = Quat::FromToRotation(Vec3::forawrd(), lineDir);
		Vec3 moveDir = q * Vec3::up();

		float percent = float(i) / float(m_worldPoints.size() - 1);
		float uvPercent = percent;
		float scalePercent = percent;

		vertex[current].position = m_worldPoints[i] + moveDir * m_width * 0.5f * scalePercent;
		vertex[current].normal = -forward;
		vertex[current].uv = Vec2(0.0f, uvPercent);
		++current;

		vertex[current].position = m_worldPoints[i] - moveDir * m_width * 0.5f * scalePercent;
		vertex[current].normal = -forward;
		vertex[current].uv = Vec2(1.0f, uvPercent);
		++current;
	}

	UnlockVertexBuffer();
}

void TrailRenderer::ResetIndexBuffer()
{
	Camera* camera = Camera::GetMainCamera();

	if (!camera)
	{
		CreateIndexBuffer(0);
		return;
	}

	if (m_numVertices < 2)
	{
		return;
	}

	Index* index = LockIndexBuffer();

	size_t current = 0;

	for (size_t i = 0; i < m_worldPoints.size() - 1; ++i)
	{
		size_t beg = i * 2;

		index[current].v0 = beg;
		index[current].v1 = beg + 1;
		index[current].v2 = beg + 2;
		++current;

		index[current].v0 = beg + 1;
		index[current].v1 = beg + 3;
		index[current].v2 = beg + 2;
		++current;
	}

	for (size_t i = 0; i < m_worldPoints.size() - 1; ++i)
	{
		size_t beg = m_worldPoints.size() * 2  + i * 2;

		index[current].v0 = beg;
		index[current].v1 = beg + 1;
		index[current].v2 = beg + 2;
		++current;

		index[current].v0 = beg + 1;
		index[current].v1 = beg + 3;
		index[current].v2 = beg + 2;
		++current;
	}

	UnlockIndexBuffer();
}

Vertex* TrailRenderer::LockVertexBuffer()
{
	Vertex* vertices = nullptr;
	m_vertices->Lock(0, sizeof(Vertex) * m_numVertices, (void**)&vertices, 0);
	return vertices;
}

Index* TrailRenderer::LockIndexBuffer()
{
	Index* index = nullptr;
	m_indices->Lock(0, sizeof(Index) * m_numVertices, (void**)&index, 0);
	return index;
}

void TrailRenderer::UnlockVertexBuffer()
{
	m_vertices->Unlock();
}

void TrailRenderer::UnlockIndexBuffer()
{
	m_indices->Unlock();
}
