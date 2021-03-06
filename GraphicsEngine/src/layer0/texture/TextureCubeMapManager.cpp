/*
 * TextureCubeMapManager.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory.h"

#include "TextureCubeMapManager.h"

using namespace std;

TextureCubeMapManager* TextureCubeMapManager::instance;

TextureCubeMapManager::TextureCubeMapManager() :
	allTextures()
{
}

TextureCubeMapManager::~TextureCubeMapManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

TextureCubeMapManager* TextureCubeMapManager::getInstance()
{
	if (!instance)
	{
		instance = new TextureCubeMapManager();
	}

	return instance;
}

void TextureCubeMapManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void TextureCubeMapManager::addTexture(const string& posX, const TextureCubeMapSP& texture)
{
	allTextures[posX] = texture;
}

TextureCubeMapSP TextureCubeMapManager::createTexture(const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(posX);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[posX] = textureFactory.createTextureCubeMap(posX, negX, posY, negY, posZ, negZ, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[posX];
	}

	return allTextures[posX];
}

TextureCubeMapSP TextureCubeMapManager::createTexture(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(filename);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[filename] = textureFactory.createTextureCubeMap(filename, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[filename];
	}

	return allTextures[filename];
}
