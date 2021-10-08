#pragma once

class SharedResourceLoader
{
public:

	static void LoadSharedResources();

private:

	static const wstring localSharedResourceDirectory;

	static const wstring localTextureResourceDirectory;
};

