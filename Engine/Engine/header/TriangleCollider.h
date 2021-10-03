#pragma once

#include "Collider.h"

class TriangleCollider : public Collider
{
	OverrideComponentFunction(Awake);

	virtual PxGeometryHolder CreateGeometry() override;

private:

	PxConvexMeshGeometry CreateTriangleGeometry() const;

private:

	PxConvexMesh* m_mesh;
};

