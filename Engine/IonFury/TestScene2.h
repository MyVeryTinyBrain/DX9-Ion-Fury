#pragma once

class TestScene2 : public Scene
{
	// Scene��(��) ���� ��ӵ�
	virtual IClonable* Clone() override;
	virtual void OnLoad(Scene* beforeScene) override;
	virtual void OnUnload(Scene* nextScene) override;
};

