#pragma once

#include "UserMeshRenderer.h"

class UserMeshBillboardRenderer : public UserMeshRenderer
{
	virtual void Render() override;

public:

	void SetFreezeX(bool value);

	void SetFreezeY(bool value);

	void SetFreezeZ(bool value);

	bool IsXFrozen() const;

	bool IsYFrozen() const;

	bool IsZFrozen() const;

	void SetIgnoreRotationX(bool value);

	void SetIgnoreRotationY(bool value);

	void SetIgnoreRotationZ(bool value);

	bool IsIgnoreRotationX() const;

	bool IsIgnoreRotationY() const;

	bool IsIgnoreRotationZ() const;

	__declspec(property(get = IsXFrozen, put = SetFreezeX)) bool freezeX;

	__declspec(property(get = IsYFrozen, put = SetFreezeY)) bool freezeY;

	__declspec(property(get = IsZFrozen, put = SetFreezeZ)) bool freezeZ;

	__declspec(property(get = IsIgnoreRotationX, put = SetIgnoreRotationX)) bool ignoreRotationX;

	__declspec(property(get = IsIgnoreRotationY, put = SetIgnoreRotationY)) bool ignoreRotationY;

	__declspec(property(get = IsIgnoreRotationZ, put = SetIgnoreRotationZ)) bool ignoreRotationZ;

private:

	bool m_freezeX = false;

	bool m_freezeY = false;

	bool m_freezeZ = false;

	bool m_ignoreRotationX = true;

	bool m_ignoreRotationZ = true;

	bool m_ignoreRotationY = true;
};

