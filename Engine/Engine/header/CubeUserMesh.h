#pragma once

#include "UserMesh.h"

class CubeUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	CubeUserMesh();

	CubeUserMesh(const wstring& localPath, bool isShared);

	virtual ~CubeUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

