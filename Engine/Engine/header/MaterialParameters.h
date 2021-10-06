#pragma once

enum class RenderQueue
{
	Background,
	Geometry,
	AlphaTest,
	GeometryLast,
	Transparent,
	Overlay,
	Max,
};

struct MaterialParameters
{
	bool m_wireFrame = false;

	CullMode m_cullMode = CullMode::CW;

	bool m_zWrite = true;

	bool m_zRead = true;

	CmpMode m_zReadMode = CmpMode::LessEqual;

	bool m_alphaTest = false;

	DWORD m_alphaRef = 0; // 0x00 ~ 0xFF

	CmpMode m_alpahTestMode = CmpMode::Greater;

	bool m_alphaBlend = false;

	BlendOpMode m_blendOperation = BlendOpMode::Add;

	BlendFactor m_srcBlendFactor = BlendFactor::SrcAlpha;

	BlendFactor m_dstBlendFactor = BlendFactor::OneMinusSrcAlpha;

	RenderQueue m_renderQueue = RenderQueue::Geometry;





	bool m_light = true;

	bool m_specular = false;

	Color m_ambient = Color::white();

	Color m_diffuse = Color::white();

	Color m_emissive = Color::black();

	Color m_specular = Color::black();

	float m_power = 1.0f;
};

