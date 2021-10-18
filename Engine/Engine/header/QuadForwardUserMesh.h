#pragma once

#include "UserMesh.h"
class QuadForwardUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	QuadForwardUserMesh();

	QuadForwardUserMesh(const wstring& localPath, bool isShared);

	virtual ~QuadForwardUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

