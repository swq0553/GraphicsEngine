/*
 * Texture1DManager.h
 *
 *  Created on: 20.12.2012
 *      Author: nopper
 */

#ifndef TEXTURE1DMANAGER_H_
#define TEXTURE1DMANAGER_H_

#include "../../UsedLibs.h"

#include "Texture1D.h"

class Texture1DManager
{

private:

	static Texture1DManager* instance;

	std::map<std::string, Texture1DSP> allTextures;

private:

	Texture1DManager();
	virtual ~Texture1DManager();

public:

	static Texture1DManager* getInstance();

	static void terminate();

	void addTexture(const std::string& key, const Texture1DSP& texture);

	Texture1DSP createTexture(const std::string& key, boost::int32_t width, GLenum format, GLenum type, const boost::uint8_t* pixels = nullptr, boost::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);

	Texture1DSP createTexture(const std::string& key, GLint internalFormat, boost::int32_t width, GLenum format, GLenum type, const boost::uint8_t* pixels = nullptr, boost::uint32_t sizeOfData = 0, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);

};

#endif /* TEXTURE1DMANAGER_H_ */
