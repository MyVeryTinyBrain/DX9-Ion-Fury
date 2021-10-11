#pragma once

#include "UserMesh.h"

class RightTriangleFrontSide : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	RightTriangleFrontSide();

	RightTriangleFrontSide(const wstring& localPath, bool isShared);

	virtual ~RightTriangleFrontSide();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;
};

