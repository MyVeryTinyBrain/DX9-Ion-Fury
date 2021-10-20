#pragma once

class ObjectContainer : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginRender);


public:

	void SetLeftTexture(const wstring& localPath);

	void SetRightTexture(const wstring& localPath);

	void SetTopTexture(const wstring& localPath);

	void SetBottomTexture(const wstring& localPath);

	void SetForwardTexture(const wstring& localPath);

	void SetBackTexture(const wstring& localPath);

private:

	class Cube* m_cube = nullptr;
};

