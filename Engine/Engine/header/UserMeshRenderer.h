#pragma once

#include "Renderer.h"

class UserMesh;

class UserMeshRenderer : public Renderer
{
	OverrideComponentFunction(Render);

public:

	bool Raycast(Vec3& hitPoint, const Vec3& worldRayPoint, const Vec3& worldRayDir);

	void SetUserMesh(const Ref<UserMesh>& userMesh);

	const Ref<UserMesh>& GetUserMesh() const;

	__declspec(property(get = GetUserMesh, put = SetUserMesh)) const Ref<UserMesh>& userMesh;

protected:

	Ref<UserMesh> m_userMesh;
};

