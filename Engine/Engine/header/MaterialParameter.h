#pragma once

struct MaterialParameter
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

	bool m_light = true;

	bool m_specular = false;
};

