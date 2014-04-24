#include "Texture.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>	// For sf::Image

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

		// Setup default filtering properties
		SetFiltering(TextureFilterType::NearestNeighbor);

		// Define a blank white texture
		float texels[] = {
			1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f
		};

		// Upload a blank white texture map to graphics card
		glTexImage2D(
			GL_TEXTURE_2D,	// Target Type
			0,				// Level Of Detail
			GL_RGB,			// Format to store in graphics card
			2,				// Image width
			2,				// Image height
			0,				// Border (has to be 0)
			GL_RGB,			// Format from image source
			GL_FLOAT,		// Data type from image source
			texels			// Pointer to image source
		);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Ctor
	Texture::Texture(const std::string& textureFilePath) :
		INameable("Unnamed Texture")
	{
		// Generate a texture handler for OpenGL
		glGenTextures(1, &_textureHandle);

		// Setup default wrapping behavior
		SetWrapping(TextureWrapType::Repeat);

		// Setup default filtering properties
		SetFiltering(TextureFilterType::NearestNeighbor);

		// Load texture image from specified file path
		sf::Image loadedImage;
		if(!loadedImage.loadFromFile(textureFilePath))
		{
			// Create a blank white texture upon load fail
			std::cout << "Resorting to a blank white texture" << std::endl;
			loadedImage.create(2, 2, sf::Color::White);
		}

		// Flip upside down to render properly in OpenGL
		loadedImage.flipVertically();

		// Upload texture to graphics card
		sf::Vector2u size = loadedImage.getSize();
		glTexImage2D(
			GL_TEXTURE_2D,				// Target Type
			0,							// Level Of Detail
			GL_RGB,						// Format to store in graphics card
			(int) size.x,				// Image width
			(int) size.y,				// Image height
			0,							// Border (has to be 0)
			GL_RGBA,					// Format from image source
			GL_UNSIGNED_BYTE,			// Data type from image source
			loadedImage.getPixelsPtr()	// Pointer to image source
		);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Dtor
	Texture::~Texture()
	{
		// Delete handler to texture
		glDeleteTextures(1, &_textureHandle);
	}

	// Routines =========================================

	// Stops all textures from being the active texture
	void Texture::StopUsingTextures()
	{
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

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

} // namespace sfew