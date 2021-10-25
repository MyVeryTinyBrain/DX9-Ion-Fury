#pragma once

class SceneMap : public Scene
{
public:

	void LoadNextScene();

protected:

	virtual wstring GetMapLocalPath() const = 0;

	virtual Scene* GetNextScene() const = 0;

	virtual IClonable* Clone() override = 0;

	virtual void OnLoad(Scene* beforeScene) override;

	virtual void OnUnload(Scene* nextScene) override;

protected:

	class Skybox* m_skybox = nullptr;
};

