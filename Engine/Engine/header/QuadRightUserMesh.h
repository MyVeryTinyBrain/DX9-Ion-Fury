#pragma once

#include "UserMesh.h"
class QuadRightUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	QuadRightUserMesh();

	QuadRightUserMesh(const wstring& localPath, bool isShared);

	virtual ~QuadRightUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

