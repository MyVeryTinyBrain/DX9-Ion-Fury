#pragma once

#include "ResourceObject.h"
#include "MaterialParameter.h"

class Material : public ResourceObject, public IClonable
{
	friend class ResourceManager;

public:

	void ApplyRenderStates();

	bool IsAlphaBlend() const;

	void SetAlphaBlend(bool value);

protected:

	// Constructor for unmanaged resource
	Material();

	// Construct for managed resource
	Material(wstring localPath, bool isShared);

	virtual ~Material();

public:

	virtual IClonable* Clone() override;

private:

	MaterialParameter m_param;

};

