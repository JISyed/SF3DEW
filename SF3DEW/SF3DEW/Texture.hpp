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

	class Texture : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Texture();
		virtual ~Texture();

		// Routines =======================

		void UseTexture();			// Makes texture the current active texture
		void SetWrapping(TextureWrapType wrapBehavior);	// Set wrapping behavior when outside standard UV coordinates

		// Properties =====================



	private:

		// Helpers ========================

		

		// Data ===========================

		GLuint _textureHandle;		// Handle to texture for OpenGL
		
	};

	
} // namespace sfew

#endif