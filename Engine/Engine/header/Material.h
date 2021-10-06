#pragma once

#include "ResourceObject.h"
#include "MaterialParameters.h"

class Material : public ResourceObject, public IClonable
{
	friend class ResourceManager;

public:

	void Apply();

protected:

	// Constructor for unmanaged resource
	Material(MaterialParameters& params);

	// Construct for managed resource
	Material(MaterialParameters& params, wstring localPath, bool isShared);

	virtual ~Material();

public:

	static Material* Create(MaterialParameters& params, const wstring& localPath, bool isShared);

	static Material* CreateUnmanaged(MaterialParameters& params);

	virtual IClonable* Clone() override;

public:

	MaterialParameters params;

};

