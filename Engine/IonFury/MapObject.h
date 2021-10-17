#pragma once

class MapObject : public Component
{
	OverrideComponentFunction(OnDestroy);

public:

	void InitializeMapObject(const wstring& textureLocalPath, const Vec2& uvScale, int iMeshType, bool hasCollider);

private:

	UserMeshRenderer* m_renderer = nullptr;

	UserMesh* m_mesh = nullptr;

	Rigidbody* m_body = nullptr;

	Collider* m_collider = nullptr;
};

