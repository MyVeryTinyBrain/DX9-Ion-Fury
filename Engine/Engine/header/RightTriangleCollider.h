#pragma once

#include "Collider.h"

class RightTriangleCollider : public Collider
{
	OverrideComponentFunction(Awake);

	virtual PxGeometryHolder CreateGeometry() override;

private:

	PxConvexMeshGeometry CreateRightTriangleGeometry() const;

private:

	PxConvexMesh* m_mesh;
};

