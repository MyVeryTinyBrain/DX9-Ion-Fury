#pragma once

class FreePerspectiveCamera : public Component
{
	OverrideComponentFunction(Update);

private:

	void MoveMouseToCenterPos();

	POINT GetMousePointInClient() const;
	
public:
	void Add_MapObject(
		bool ColiderExistence
		, const tag_t& tag = L"test"
		, const wstring& ObjName = L"defaultName"
		, const wstring& localPathMesh = BuiltInCubeUserMesh
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

