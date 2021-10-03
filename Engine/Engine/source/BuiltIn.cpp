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
}

#include "CubeUserMesh.h"
#include "SphereUserMesh.h"
#include "CyilinderUserMesh.h"
#include "QuadUserMesh.h"
#include "CapsuleUserMesh.h"
#include "RightTriangleUserMesh.h"
#include "TriangleUserMesh.h"

void BuiltIn::MakeUserMeshResources()
{
    UserMesh::Create<CubeUserMesh>(BuiltInCubeUserMesh, true);
    UserMesh::Create<SphereUserMesh>(BuiltInSphereUserMesh, true);
    UserMesh::Create<CyilinderUserMesh>(BuiltInCyilinderUserMesh, true);
    UserMesh::Create<QuadUserMesh>(BuiltInQuadUserMesh, true);
    UserMesh::Create<CapsuleUserMesh>(BuiltInCapsuleUserMesh, true);
    UserMesh::Create<RightTriangleUserMesh>(BuiltInRightTriangleUserMesh, true);
    UserMesh::Create<TriangleUserMesh>(BuiltInTriangleUserMesh, true);
}

#include "Texture.h"

void BuiltIn::MakeTextureResources()
{
    Texture::CreateInDirectX(128, 128, Color::black(), BuiltInBlackTexture, true);
    Texture::CreateInDirectX(128, 128, Color::white(), BuiltInWhiteTexture, true);
    Texture::CreateInDirectX(128, 128, Color::red(), BuiltInRedTexture, true);
    Texture::CreateInDirectX(128, 128, Color::green(), BuiltInGreenTexture, true);
    Texture::CreateInDirectX(128, 128, Color::blue(), BuiltInBlueTexture, true);
}
