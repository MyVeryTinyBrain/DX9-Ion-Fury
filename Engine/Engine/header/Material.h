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
	Material();

	// Construct for managed resource
	Material(wstring localPath, bool isShared);

	virtual ~Material();

public:



public:

	virtual IClonable* Clone() override;

public:

	MaterialParameters params;

};

