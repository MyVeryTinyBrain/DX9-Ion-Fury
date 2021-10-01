#pragma once

#include "Object.h"

class SceneObject : public Object
{
protected:

	virtual void OnBeforeDestroy() {}

	virtual void OnDestroy() {}

public:

	SceneObject();

	SceneObject(wstring name);

	virtual ~SceneObject();

	void Destroy();

	bool IsShouldDestroy() const;

	DefineGetReferenceTo(SceneObject);

public:

	Delegate<void(SceneObject*)> OnDestroyCallback;

protected:

	bool m_shouldDestroy = false;
};

