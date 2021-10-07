#include "EngineBase.h"
#include "SharedResourceLoader.h"
#include "Path.h"
#include "Texture.h"

const wstring SharedResourceLoader::localSharedResourceDirectory = L"../SharedResource/";

const wstring SharedResourceLoader::localTextureResourceDirectory = localSharedResourceDirectory + L"Texture/";

void SharedResourceLoader::LoadSharedResources()
{
	{	// Load png to textures
		auto pathes = Path::QueryFilePath(localTextureResourceDirectory, L".png");
		for (auto& path : pathes)
		{
			Texture::CreateFromFile(path, true);
		}
	}
}
