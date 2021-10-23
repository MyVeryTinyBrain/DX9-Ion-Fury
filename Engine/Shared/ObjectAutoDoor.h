#pragma once

#include "IUsable.h"
#include "IDontDeactive.h"

class ObjectAutoDoor : public Component, public IUsable, public IDontDeactive
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	virtual void OnUse(bool valid) override;

public:

	void Toggle();

	void Open();

	void Close();

	void SetAutoOpen(bool value);

protected:

	GameObject* m_root = nullptr;

	GameObject* m_leftFrameObj = nullptr;

	GameObject* m_rightFrameObj = nullptr;

	GameObject* m_topFrameObj = nullptr;

	GameObject* m_bottomFrameObj = nullptr;

	GameObject* m_doorObj = nullptr;

	Vec3 m_targetLocalPosition = Vec3::zero();

protected:

	bool m_autoOpen = true;

private:

	bool m_state = false;
};

