#pragma once

struct Vertex
{
	Vec3 position;
	Vec3 normal;
	Vec2 uv;
	constexpr static DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};

struct CubeTexVertex
{
	constexpr static DWORD FVF = 0;
};

