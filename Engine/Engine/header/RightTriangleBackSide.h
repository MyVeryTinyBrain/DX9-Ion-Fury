#pragma once

#include "UserMesh.h"

class RightTriangleBackSide : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	RightTriangleBackSide();

	RightTriangleBackSide(const wstring& localPath, bool isShared);

	virtual ~RightTriangleBackSide();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

