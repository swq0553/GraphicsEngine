/*
 * Texture1DArrayManager.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "Texture1DArrayManager.h"

using namespace std;
using namespace boost;

Texture1DArrayManager* Texture1DArrayManager::instance;

Texture1DArrayManager::Texture1DArrayManager() :
		allTextures()
{
}

Texture1DArrayManager::~Texture1DArrayManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

Texture1DArrayManager* Texture1DArrayManager::getInstance()
{
	if (!instance)
	{
		instance = new Texture1DArrayManager();
	}

	return instance;
}

void Texture1DArrayManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void Texture1DArrayManager::addTexture(const string& key, const Texture1DArraySP& texture)
{
	allTextures[key] = texture;
}

Texture1DArraySP Texture1DArrayManager::createTexture(const string& key, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture1DArray(width, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture1DArraySP Texture1DArrayManager::createTexture(const string& key, GLint internalFormat, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture1DArray(internalFormat, width, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}


