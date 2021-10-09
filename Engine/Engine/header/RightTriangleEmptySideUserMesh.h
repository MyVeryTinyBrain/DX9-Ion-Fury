#pragma once

#include "UserMesh.h"

class RightTriangleEmptySideUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	RightTriangleEmptySideUserMesh();

	RightTriangleEmptySideUserMesh(const wstring& localPath, bool isShared);

	virtual ~RightTriangleEmptySideUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

