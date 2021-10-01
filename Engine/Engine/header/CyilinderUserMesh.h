#pragma once

#include "UserMesh.h"

class CyilinderUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	CyilinderUserMesh();

	CyilinderUserMesh(const wstring& localPath, bool isShared);

	virtual ~CyilinderUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;

private:

	unsigned int m_slice = 32;
};

