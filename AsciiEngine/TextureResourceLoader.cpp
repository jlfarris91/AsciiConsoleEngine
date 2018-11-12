#include "TextureResourceLoader.h"
#include "Shared/Exception.h"

#include "Texture.h"
#include "ConsoleGL\ITexture.h"
#include "ConsoleGL\RenderUtility.h"
#include <Shared/Path.h>

TextureResourceLoader::TextureResourceLoader()
    : ResourceLoader("Texture", ".asc")
{
}

AssetHandle TextureResourceLoader::Load(StringParam filename)
{
    auto &&rawTexture = ConsoleGL::RenderUtility::LoadTexture(filename.c_str());
    if (rawTexture == nullptr)
    {
        throw Exception("Could not load texture at '%s'", filename.c_str());
    }

    auto &&texture = Texture::New(rawTexture);
    texture->Name = Path::GetFileName(filename);
    return texture;
}