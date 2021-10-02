#pragma once

#include "UserMesh.h"

class TriangleUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	TriangleUserMesh();

	TriangleUserMesh(const wstring& localPath, bool isShared);

	virtual ~TriangleUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

