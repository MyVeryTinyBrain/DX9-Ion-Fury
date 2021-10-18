#pragma once

class TrailRenderer : public Renderer
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	OverrideComponentFunction(LateUpdate);

	virtual void Render() override;

public:

	void AddPoint(const Vec3& point);

	void RemoveFirstPoint();

	void RemoveLastPoint();

	size_t GetPointCount() const;

	float GetWidth() const;

	void SetWidth(float value);

	__declspec(property(get = GetWidth, put = SetWidth)) float width;

private:

	void ResetBuffers();

	void CreateVertexBuffer(unsigned int numVertices);

	void CreateIndexBuffer(unsigned int numIndices);

	void ResetVertexBuffer();

	void ResetIndexBuffer();

	Vertex* LockVertexBuffer();

	Index* LockIndexBuffer();

	void UnlockVertexBuffer();

	void UnlockIndexBuffer();

private:

	unsigned int m_beforePoints = 0;

	std::vector<Vec3> m_worldPoints;

	IDirect3DVertexBuffer9* m_vertices = nullptr;

	IDirect3DIndexBuffer9* m_indices = nullptr;

	unsigned int m_numVertices = 0;
	
	unsigned int m_numIndices = 0;

	float m_width = 0.5f;
};

