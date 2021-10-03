#pragma once

#include "UserMesh.h"

class RightTriangleUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	RightTriangleUserMesh();

	RightTriangleUserMesh(const wstring& localPath, bool isShared);

	virtual ~RightTriangleUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

