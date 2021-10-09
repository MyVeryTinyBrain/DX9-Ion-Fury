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

	float GetHalfHeight() const;

	void SetHalfHeight(float value);

	float GetRadius() const;

	void SetRaidus(float value);

	__declspec(property(get = GetHalfHeight, put = SetHalfHeight)) float halfHeight;

	__declspec(property(get = GetRadius, put = SetRaidus)) float radius;

private:

	unsigned int m_slice = 32;

	float m_halfHeight = 0.5f;

	float m_radius = 0.5f;
};

