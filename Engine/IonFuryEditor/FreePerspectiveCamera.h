#pragma once

#include "EditorEnum.h"

class FreePerspectiveCamera : public Component
{
	OverrideComponentFunction(Update);

private:

	void MoveMouseToCenterPos();

	POINT GetMousePointInClient() const;
	
public:
	void Add_MapObject(
		Vec2 UVScale = Vec2(1.f, 1.f)
		, COMBOBOX comboBox = COMBOBOX::Cyilinder
		, const tag_t& tag = L""
		, const wstring& ObjName = L""
		, const wstring& localPathTexture = L"../SharedResource/Texture/object/brick.jpg"
	);

	//void Add_Trigger(
	//	const tag_t& tag = L"trigger"
	//	, const wstring& ObjName = L""
	//)


private:

	float m_linearSpeed = 2;

	float m_accelerateFactor = 5.0f;

	float m_angularSpeed = 45;
};

