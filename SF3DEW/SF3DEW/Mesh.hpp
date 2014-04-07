// Mesh
// Abstraction for mesh data and vertex buffer objects
//
// Written by Jibran Syed (4-6-2014)

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <vector>

#include "INameable.hpp"

namespace sfew
{
	class Mesh : sf::NonCopyable, INameable
	{
	public:

		// Ctor/Dtor ======================

		Mesh(const std::vector<float>& newVertexDataArray);
		virtual ~Mesh();

		// Routines =======================

		

		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		GLuint _vbo;		// Handle to vertex data in shader
		
	};

	
} // namespace sfew

#endif