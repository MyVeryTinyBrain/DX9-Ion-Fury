#pragma once

class FreePerspectiveCamera : public Component
{
	OverrideComponentFunction(Update);

private:

	void MoveMouseToCenterPos();

	POINT GetMousePointInClient() const;
	
public:
	void Add_Object_Sample(
		const tag_t& tag = L"test"
		, const wstring& ObjName = L"defaultName"
		, const wstring& localPathMesh = BuiltInCubeUserMesh
		, const wstring& localPathTexture = BuiltInWhiteTexture
	);

	void AddLight( const wstring& LightName , const wstring& LightType);

private:

	float m_linearSpeed = 2;

	float m_accelerateFactor = 5.0f;

	float m_angularSpeed = 45;
};

