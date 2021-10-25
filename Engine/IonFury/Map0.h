#pragma once

#include "SceneMap.h"

class Map0 : public SceneMap
{
	virtual void OnLoad(Scene* beforeScene) override;

	virtual wstring GetMapLocalPath() const override;

	virtual Scene* GetNextScene() const override;

	virtual IClonable* Clone() override;
};

