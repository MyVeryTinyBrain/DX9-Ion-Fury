#pragma once

class TestScene3 : public Scene
{

	// Scene��(��) ���� ��ӵ�
	virtual IClonable* Clone() override;
	virtual void OnLoad(Scene* beforeScene) override;
	virtual void OnUnload(Scene* nextScene) override;



	void AddSkyBox();
	void AddMonster();
};

