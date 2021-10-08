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

	__declspec(property(get = IsXFrozen, put = SetFreezeX)) bool freezeX;

	__declspec(property(get = IsYFrozen, put = SetFreezeY)) bool freezeY;

	__declspec(property(get = IsZFrozen, put = SetFreezeZ)) bool freezeZ;

private:

	bool m_freezeX;

	bool m_freezeY;

	bool m_freezeZ;
};

