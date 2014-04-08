#include "Texture.hpp"

#include <iostream>
#include <fstream>

namespace sfew
{
	// Ctor/Dtor ========================================

	Texture::Texture() : INameable("Unnamed Texture")
	{
		// Generate a texture handler for OpenGL
		glGenTextures(1, &_textureHandle);
	}

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
		case sfew::TextureWrapType::Repeat:
			oglWrapBehavior = GL_REPEAT; break;
		case sfew::TextureWrapType::MirroredRepeat:
			oglWrapBehavior = GL_MIRRORED_REPEAT; break;
		case sfew::TextureWrapType::StretchedEdge:
			oglWrapBehavior = GL_CLAMP_TO_EDGE; break;
		case sfew::TextureWrapType::None:
			oglWrapBehavior = GL_CLAMP_TO_BORDER; break;
		}

		// Set wrapping behavior for both U (aka S) and V (aka T) coordinates
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, oglWrapBehavior);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, oglWrapBehavior);
	}

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew