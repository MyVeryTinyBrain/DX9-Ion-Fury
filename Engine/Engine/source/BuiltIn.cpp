#include "EngineBase.h"
#include "BuiltIn.h"
#include "BuiltInResources.h"

bool BuiltIn::g_made = false;

void BuiltIn::MakeBuiltInResources()
{
	if (g_made)
		return;

	g_made = true;

    MakeUserMeshResources();
    MakeTextureResources();
    MakeMaterialResources();
}

#include "CubeUserMesh.h"
#include "SphereUserMesh.h"
#include "CyilinderUserMesh.h"
#include "QuadUserMesh.h"
#include "CapsuleUserMesh.h"
#include "RightTriangleUserMesh.h"
#include "TriangleUserMesh.h"
#include "RightTriangleEmptySideUserMesh.h"
#include "RightTriangleBackSide.h"
#include "RightTriangleFrontSide.h"

void BuiltIn::MakeUserMeshResources()
{
    UserMesh::Create<CubeUserMesh>(BuiltInCubeUserMesh, true);
    UserMesh::Create<SphereUserMesh>(BuiltInSphereUserMesh, true);
    UserMesh::Create<CyilinderUserMesh>(BuiltInCyilinderUserMesh, true);
    UserMesh::Create<QuadUserMesh>(BuiltInQuadUserMesh, true);
    UserMesh::Create<CapsuleUserMesh>(BuiltInCapsuleUserMesh, true);
    UserMesh::Create<RightTriangleUserMesh>(BuiltInRightTriangleUserMesh, true);
    UserMesh::Create<TriangleUserMesh>(BuiltInTriangleUserMesh, true);
    UserMesh::Create<RightTriangleEmptySideUserMesh>(BuiltInRightTriangleEmptySideUserMesh, true);
    UserMesh::Create<RightTriangleBackSide>(BuiltInRightTriangleBackSideUserMesh, true);
    UserMesh::Create<RightTriangleFrontSide>(BuiltInRightTriangleFrontSideUserMesh, true);
}

#include "Texture.h"

void BuiltIn::MakeTextureResources()
{
    Texture::CreateInDirectX(128, 128, Color::black(), BuiltInBlackTexture, true);
    Texture::CreateInDirectX(128, 128, Color::white(), BuiltInWhiteTexture, true);
    Texture::CreateInDirectX(128, 128, Color::red(), BuiltInRedTexture, true);
    Texture::CreateInDirectX(128, 128, Color::green(), BuiltInGreenTexture, true);
    Texture::CreateInDirectX(128, 128, Color::blue(), BuiltInBlueTexture, true);

    Texture::CreateInDirectX(128, 128, Color(1, 1, 1, 0.25f), BuiltInTransparentWhiteTexture, true);
    Texture::CreateInDirectX(128, 128, Color(0, 0, 0, 0.25f), BuiltInTransparentBlackTexture, true);
    Texture::CreateInDirectX(128, 128, Color(1, 0, 0, 0.25f), BuiltInTransparentRedTexture, true);
    Texture::CreateInDirectX(128, 128, Color(0, 1, 0, 0.25f), BuiltInTransparentGreenTexture, true);
    Texture::CreateInDirectX(128, 128, Color(0, 0, 1, 0.25f), BuiltInTransparentBlueTexture, true);
}

#include "Material.h"

void BuiltIn::MakeMaterialResources()
{
    {
        MaterialParameters params;
        params.zWrite = false;
        params.useLight = false;
        params.renderQueue = RenderQueue::Background;
        Material::Create(params, BuiltInBackgroundMaterial, true);
    }
    {
        MaterialParameters params;
        params.zWrite = false;
        params.cullMode = CullMode::None;
        params.useLight = false;
        params.renderQueue = RenderQueue::Background;
        Material::Create(params, BuiltInSkyboxBackgroundMaterial, true);
    }
    {
        MaterialParameters params;
        params.renderQueue = RenderQueue::Priority;
        Material::Create(params, BuiltInPriorityMaterial, true);
    }
    {
        MaterialParameters params;
        params.renderQueue = RenderQueue::Priority;
        params.useLight = false;
        Material::Create(params, BuiltInNolightPriorityMaterial, true);
    }
    {
        MaterialParameters params;
        Material::Create(params, BuiltInGeometryMaterial, true);
    }
    {
        MaterialParameters params;
        params.useLight = false;
        Material::Create(params, BuiltInNolightGeometryMaterial, true);
    }
    {
        MaterialParameters params;
        params.renderQueue = RenderQueue::GeometryLast;
        Material::Create(params, BuiltInGeometryLastMaterial, true);
    }
    {
        MaterialParameters params;
        params.renderQueue = RenderQueue::GeometryLast;
        params.useLight = false;
        Material::Create(params, BuiltInNolightGeometryLastMaterial, true);
    }
    {
        MaterialParameters params;
        params.alphaTest = true;
        params.renderQueue = RenderQueue::AlphaTest;
        Material::Create(params, BuiltInAlphaTestMaterial, true);
    }
    {
        MaterialParameters params;
        params.alphaTest = true;
        params.useLight = false;
        params.renderQueue = RenderQueue::AlphaTest;
        Material::Create(params, BuiltInNolightAlphaTestMaterial, true);
    }
    {
        MaterialParameters params;
        params.alphaTest = true;
        params.alphaBlend = true;
        params.renderQueue = RenderQueue::Transparent;
        Material::Create(params, BuiltInTransparentMaterial, true);
    }
    {
        MaterialParameters params;
        params.alphaTest = true;
        params.alphaBlend = true;
        params.useLight = false;
        params.renderQueue = RenderQueue::Transparent;
        Material::Create(params, BuiltInNolightTransparentMaterial, true);
    }
    {
        MaterialParameters params;
        params.zRead = false;
        params.zWrite = false;
        params.alphaTest = true;
        params.alphaBlend = true;
        params.useLight = false;
        params.renderQueue = RenderQueue::Overlay;
        Material::Create(params, BuiltInOverlayMaterial, true);
    }
    {
        MaterialParameters params;
        params.zRead = false;
        params.zWrite = false;
        params.alphaTest = true;
        params.alphaBlend = true;
        params.useLight = true;
        params.renderQueue = RenderQueue::Overlay;
        Material::Create(params, BuiltInLightOverlayMaterial, true);
    }
}
