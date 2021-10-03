#pragma once

#include "UserMesh.h"

class CapsuleUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	CapsuleUserMesh();

	CapsuleUserMesh(const wstring& localPath, bool isShared);

	virtual ~CapsuleUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;

private:

	unsigned int m_step = 32;

	float m_halfHeight = 0.5f;
};

