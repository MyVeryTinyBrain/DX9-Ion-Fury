#pragma once

class BuiltIn
{
public:

	static void MakeBuiltInResources();

private:

	static void MakeUserMeshResources();

	static void MakeTextureResources();

private:

	static bool g_made;
};

