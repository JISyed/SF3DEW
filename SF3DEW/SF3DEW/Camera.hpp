// Camera
// Abstraction view and projection matrix
//
// Written by Jibran Syed (4-7-2014)

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "LinearAlgebraTypes.hpp"
#include "INameable.hpp"

namespace sfew
{
	class Camera : sf::NonCopyable, INameable
	{
	public:
		
		// Ctor/Dtor ======================
		
		Camera();
		virtual ~Camera();

		// Routines =======================

		

		// Properties =====================

		void SetWindowSize(unsigned int width, unsigned int height);	// Define window size for rendering

	private:
		
		// Helpers ========================

		

		// Data ===========================

		unsigned int _windowWidth;		// Window width in pixels
		unsigned int _windowHeight;		// Window height in pixels

	};
	
} // namespace sfew

#endif