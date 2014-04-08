// Texture
// Represents a single texture in OpenGL
// Only supports GL_TEXTURE_2D
//
// Written by Jibran Syed (4-8-2014)

#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <string>

#include "INameable.hpp"

namespace sfew
{
	enum class TextureWrapType : char
	{
		Repeat,
		MirroredRepeat,
		StretchedEdge,
		None
	};

	enum class TextureFilterType : char
	{
		NearestNeighbor,
		Bilinear,
		Trilinear
	};

	class Texture : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Texture();
		Texture(const std::string& textureFilePath);
		virtual ~Texture();

		// Routines =======================

		void UseTexture();			// Makes texture the current active texture
		void SetWrapping(TextureWrapType wrapBehavior);	// Set wrapping behavior when outside standard UV coordinates
		void SetFiltering(TextureFilterType filter);	// Set texture filtering (how texture gets sampled)

		// Properties =====================



	private:

		// Helpers ========================

		

		// Data ===========================

		GLuint _textureHandle;				// Handle to texture for OpenGL
		
	};

	
} // namespace sfew

#endif