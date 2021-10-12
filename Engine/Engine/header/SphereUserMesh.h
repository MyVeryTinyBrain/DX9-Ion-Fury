#pragma once

#include "UserMesh.h"

class SphereUserMesh : public UserMesh
{
	friend class UserMesh;
	friend class ResourceManager;

private:

	SphereUserMesh();

	SphereUserMesh(const wstring& localPath, bool isShared);

	virtual ~SphereUserMesh();

private:

	virtual void InitializeNums(unsigned int& numVertices, unsigned int& numIncides) override;

	virtual void InitializeVertices() override;

	virtual void InitializeIndices() override;

public:

	virtual IClonable* Clone() override;

	float GetRadius() const;

	void SetRaidus(float value);

	__declspec(property(get = GetRadius, put = SetRaidus)) float radius;

private:

	unsigned int m_step = 32;

	float m_radius = 0.5f;
};

