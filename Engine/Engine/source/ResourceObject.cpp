#include "EngineBase.h"
#include "ResourceObject.h"

#include <filesystem>

namespace fs = std::filesystem;

using path = fs::path;

ResourceObject::ResourceObject() : Object()
{
	m_isUnmanaged = true;
}

ResourceObject::ResourceObject(wstring localPath, bool isShared)
	: Object(path(localPath).filename())
{
	m_localPath = localPath;

	m_isShared = isShared;

	m_isUnmanaged = false;
}

ResourceObject::~ResourceObject()
{
}

bool ResourceObject::IsShared() const
{
	return m_isShared;
}

bool ResourceObject::IsUnmanaged() const
{
	return m_isUnmanaged;
}

void ResourceObject::ReleaseUnmanaged()
{
	if (!m_isUnmanaged)
		return;

	delete this;
}

const wstring& ResourceObject::GetLocalPath() const
{
	return m_localPath;
}
