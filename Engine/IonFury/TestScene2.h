#pragma once

class TestScene2 : public Scene
{
	// Scene을(를) 통해 상속됨
	virtual IClonable* Clone() override;
	virtual void OnLoad(Scene* beforeScene) override;
	virtual void OnUnload(Scene* nextScene) override;
};

