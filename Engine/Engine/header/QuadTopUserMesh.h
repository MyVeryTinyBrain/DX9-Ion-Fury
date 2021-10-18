#pragma once

#include "UserMesh.h"
class QuadTopUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	QuadTopUserMesh();

	QuadTopUserMesh(const wstring& localPath, bool isShared);

	virtual ~QuadTopUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

