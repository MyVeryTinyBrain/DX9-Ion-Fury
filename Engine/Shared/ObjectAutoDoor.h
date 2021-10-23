#pragma once

class ObjectAutoDoor : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

protected:

	GameObject* m_root = nullptr;

	GameObject* m_leftFrameObj = nullptr;

	GameObject* m_rightFrameObj = nullptr;

	GameObject* m_topFrameObj = nullptr;

	GameObject* m_bottomFrameObj = nullptr;

	GameObject* m_doorObj = nullptr;

	Vec3 m_targetLocalPosition = Vec3::zero();

public:

	bool autoOpen = true;
};

