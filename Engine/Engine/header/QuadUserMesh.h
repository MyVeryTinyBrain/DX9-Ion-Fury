#pragma once

#include "UserMesh.h"
class QuadUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	QuadUserMesh();

	QuadUserMesh(const wstring& localPath, bool isShared);

	virtual ~QuadUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

