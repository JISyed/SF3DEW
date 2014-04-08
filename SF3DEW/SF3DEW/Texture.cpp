#include "Texture.hpp"

#include <iostream>
#include <fstream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Default Ctor
	Texture::Texture() : 
		INameable("Blank Texture")
	{
		// Generate a texture handler for OpenGL
		glGenTextures(1, &_textureHandle);

		// Setup default wrapping behavior
		SetWrapping(TextureWrapType::Repeat);

		// Upload a blank white texture map to graphics card
		float texels[] = {
			0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
		};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, texels);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Setup default filtering properties
		SetFiltering(TextureFilterType::NearestNeighbor);
	}

	// Ctor
	Texture::Texture(const std::string& textureFilePath) :
		INameable("Unnamed Texture")
	{
		// Generate a texture handler for OpenGL
		glGenTextures(1, &_textureHandle);

		// Setup default wrapping behavior
		SetWrapping(TextureWrapType::Repeat);

		glGenerateMipmap(GL_TEXTURE_2D);

		// Setup default filtering properties
		SetFiltering(TextureFilterType::NearestNeighbor);
	}

	// Dtor
	Texture::~Texture()
	{
		// Delete handler to texture
		glDeleteTextures(1, &_textureHandle);
	}

	// Routines =========================================

	// Makes texture the current active texture
	void Texture::UseTexture()
	{
		glBindTexture(GL_TEXTURE_2D, _textureHandle);
	}

	// Set wrapping behavior when outside standard UV coordinates
	void Texture::SetWrapping(TextureWrapType wrapBehavior)
	{
		// Make sure this texture is active first
		glBindTexture(GL_TEXTURE_2D, _textureHandle);

		// Get the wrap behavior in something OpenGL understands
		GLint oglWrapBehavior;
		switch (wrapBehavior)
		{
		case TextureWrapType::Repeat:
			oglWrapBehavior = GL_REPEAT; break;
		case TextureWrapType::MirroredRepeat:
			oglWrapBehavior = GL_MIRRORED_REPEAT; break;
		case TextureWrapType::StretchedEdge:
			oglWrapBehavior = GL_CLAMP_TO_EDGE; break;
		case TextureWrapType::None:
			oglWrapBehavior = GL_CLAMP_TO_BORDER; break;
		}

		// Set wrapping behavior for both U (aka S) and V (aka T) coordinates
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, oglWrapBehavior);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, oglWrapBehavior);
	}

	// Set texture filtering (how texture gets sampled)
	void Texture::SetFiltering(TextureFilterType filter)
	{
		// Make sure this texture is active first
		glBindTexture(GL_TEXTURE_2D, _textureHandle);

		// Get filtering in something OpenGL understands
		GLint oglMinFilter;
		GLint oglMagFilter;
		switch (filter)
		{
		case TextureFilterType::NearestNeighbor:
			oglMinFilter = GL_NEAREST_MIPMAP_NEAREST;
			oglMagFilter = GL_NEAREST;
			break;
		case TextureFilterType::Bilinear:
			oglMinFilter = GL_LINEAR_MIPMAP_NEAREST;
			oglMagFilter = GL_LINEAR;
			break;
		case TextureFilterType::Trilinear:
			oglMinFilter = GL_LINEAR_MIPMAP_LINEAR;
			oglMagFilter = GL_LINEAR;
			break;
		}

		// Apply filtering properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, oglMinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, oglMagFilter);
	}

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew