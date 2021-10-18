#pragma once

#include "EditorEnum.h"

class Pickable;
class HandlingObject;

class FreePerspectiveCamera : public Component
{
	OverrideComponentFunction(Update);

private:

	void MoveMouseToCenterPos();

	POINT GetMousePointInClient() const;

public:
	Pickable* Add_MapObject(
		bool ColliderExistence = false
		, Vec3 Size = Vec3(1.f, 1.f, 1.f)
		, Vec3 Rotation = Vec3(0.f, 0.f, 0.f)
		, Vec2 UVScale = Vec2(1.f, 1.f)
		, COMBOBOX comboBox = COMBOBOX::Cyilinder
		, const tag_t& tag = L""
		, const wstring& ObjName = L""
		, const wstring& localPathTexture = L"../SharedResource/Texture/object/brick.jpg"
	);

	Pickable* Add_TriggerObject(int cnt);

	Pickable* Add_EventObject(Pickable* Trigger, int cnt);

	HandlingObject* Add_HandlingObject(int cnt);

private:

	float m_linearSpeed = 2;

	float m_accelerateFactor = 5.0f;

	float m_angularSpeed = 45;
};

