// Object Renderer
// Draws a mesh-material pairing (single 3D object)
//
// Written by Jibran Syed (4-13-2014)

#ifndef SFEW_OBJECT_RENDERER_H
#define SFEW_OBJECT_RENDERER_H

#include <memory>
#include <SFML/System/NonCopyable.hpp>

#include "Mesh.hpp"
#include "Material.hpp"

namespace sfew
{
	class ObjectRenderer : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		ObjectRenderer();
		~ObjectRenderer();

		// Routines =======================

		void Draw();				// Draws the 3D entity

		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		
		
	};

	
} // namespace sfew

#endif