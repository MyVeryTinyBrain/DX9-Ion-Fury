#pragma once

#include "Object.h"

class ResourceObject abstract : public Object
{
	friend class ResourceManager;

protected:

	// Constructor for unmanaged resource
	ResourceObject();

	// Construct for managed resource
	ResourceObject(wstring localPath, bool isShared);

	virtual ~ResourceObject();

public:

	void ReleaseUnmanaged();

	const wstring& GetLocalPath() const;

	bool IsShared() const;

	bool IsUnmanaged() const;

	__declspec(property(get = GetLocalPath)) const wstring& localPath;

	__declspec(property(get = IsShared)) bool isShared;

	__declspec(property(get = IsUnmanaged)) bool isUnmanaged;

private:

	wstring m_localPath = L"";

	bool m_isShared = false;

	bool m_isUnmanaged = true;
};
