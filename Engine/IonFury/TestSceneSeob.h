#pragma once

class TestSceneSeob : public Scene
{
	virtual IClonable* Clone() override;

	virtual void OnLoad(Scene* beforeScene) override;

	virtual void OnUnload(Scene* nextScene) override;
};

