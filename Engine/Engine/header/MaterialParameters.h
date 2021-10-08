#pragma once

enum class RenderQueue
{
	Background,
	Priority,
	Geometry,
	AlphaTest,
	GeometryLast,
	Transparent,
	Overlay,
	Max,
};

struct MaterialParameters
{
	bool wireFrame = false;

	CullMode cullMode = CullMode::CCW;

	bool zWrite = true;

	bool zRead = true;

	CmpMode zReadMode = CmpMode::LessEqual;

	bool alphaTest = false;

	DWORD alphaRef = 0; // 0x00 ~ 0xFF (0 ~ 255)

	CmpMode alpahTestMode = CmpMode::Greater;

	bool alphaBlend = false;

	BlendOpMode blendOperation = BlendOpMode::Add;

	BlendFactor srcBlendFactor = BlendFactor::SrcAlpha;

	BlendFactor dstBlendFactor = BlendFactor::OneMinusSrcAlpha;

	RenderQueue renderQueue = RenderQueue::Geometry;




	bool useLight = true;

	bool useSpecular = false;

	Color ambient = Color::white();

	Color diffuse = Color::white();

	Color emissive = Color::black();

	Color specular = Color::white();

	float power = 1.0f;
};

