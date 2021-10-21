#pragma once

class ObjectAutoDoor : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	void Toggle();

	void Open();

	void Close();

protected:

	GameObject* m_root = nullptr;

	GameObject* m_leftFrameObj = nullptr;

	GameObject* m_rightFrameObj = nullptr;

	GameObject* m_topFrameObj = nullptr;

	GameObject* m_bottomFrameObj = nullptr;

	GameObject* m_doorObj = nullptr;

	Vec3 m_targetLocalPosition = Vec3::zero();

protected:

	bool autoOpen = true;

private:

	bool m_state = false;
};

